#include <iostream>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <array>

using Matrix = std::vector<std::vector<std::vector<std::array<double, 3>>>>;

constexpr size_t E = 0;
constexpr size_t H = 1;

// Taille de la matrice de travail (un côté)
static const int MATRIX_SIZE = 100;
static const int MATRIX_DEPTH = 3;
static const int OFFSET_I = MATRIX_SIZE * MATRIX_SIZE * MATRIX_DEPTH;
static const int OFFSET_J = MATRIX_SIZE * MATRIX_DEPTH;
static const int OFFSET_K = MATRIX_DEPTH;
static const int BUFFER_SIZE = MATRIX_SIZE * MATRIX_SIZE * MATRIX_SIZE * MATRIX_DEPTH * sizeof(double);
// Tampon générique à utiliser pour créer le fichier
char buffer_[BUFFER_SIZE];

void wait_signal()
{
    // Attend une entrée (ligne complète avec \n) sur stdin.
    std::string msg;
    std::cin >> msg;
}

void ack_signal()
{
    // Répond avec un message vide.
    std::cout << "" << std::endl;
}

template<size_t isH>
Matrix curl(const Matrix& mtx)
{
    Matrix curl {100, std::vector<std::vector<std::array<double, 3>>>{100, std::vector<std::array<double, 3>>{100,}}};


    auto threadX = [](Matrix& curl, const Matrix& mtx)
    {
        auto threadX_1 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = 0; i < MATRIX_SIZE/2 -1; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (j < MATRIX_SIZE -1)
                            curl[i][j+isH][k][0] += mtx[i][j+1][k][2] - mtx[i][j][k][2];

                        if (k < MATRIX_SIZE -1)
                            curl[i][j][k+isH][0] -= mtx[i][j][k+1][1] - mtx[i][j][k][1];
                    }
                }
            }   
        };

        auto threadX_2 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = MATRIX_SIZE/2; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (j < MATRIX_SIZE -1)
                            curl[i][j+isH][k][0] += mtx[i][j+1][k][2] - mtx[i][j][k][2];

                        if (k < MATRIX_SIZE -1)
                            curl[i][j][k+isH][0] -= mtx[i][j][k+1][1] - mtx[i][j][k][1];
                    }
                }
            }
        };

        std::thread t1 (threadX_1, std::ref(curl), mtx);
        std::thread t2 (threadX_2, std::ref(curl), mtx);

        t1.join();
        t2.join();
    };

    auto threadY = [](Matrix& curl, const Matrix& mtx)
    {
        auto threadY_1 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = 0; i < MATRIX_SIZE/2 -1; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (k < MATRIX_SIZE -1)
                            curl[i][j][k+isH][1] += mtx[i][j][k+1][0] - mtx[i][j][k][0];

                        if (i < MATRIX_SIZE -1)
                            curl[i+isH][j][k][1] -= mtx[i+1][j][k][2] - mtx[i][j][k][2];
                    }
                }
            }
        };

        auto threadY_2 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = MATRIX_SIZE/2; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (k < MATRIX_SIZE -1)
                            curl[i][j][k+isH][1] += mtx[i][j][k+1][0] - mtx[i][j][k][0];

                        if (i < MATRIX_SIZE -1)
                            curl[i+isH][j][k][1] -= mtx[i+1][j][k][2] - mtx[i][j][k][2];
                    }
                }
            }
        };

        std::thread t1 (threadY_1, std::ref(curl), mtx);
        std::thread t2 (threadY_2, std::ref(curl), mtx);

        t1.join();
        t2.join();
    };

    auto threadZ = [](Matrix& curl, const Matrix& mtx)
    {
        auto threadZ_1 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = 0; i < MATRIX_SIZE/2 -1; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (i < MATRIX_SIZE -1)
                            curl[i+isH][j][k][2] += mtx[i+1][j][k][1] - mtx[i][j][k][1];

                        if (j < MATRIX_SIZE - 1)
                            curl[i][j+isH][k][2] -= mtx[i][j+1][k][0] - mtx[i][j][k][0];
                    }
                }
            }
        };

        auto threadZ_2 = [](Matrix& curl, const Matrix& mtx)
        {
            for (int i = MATRIX_SIZE/2; i < MATRIX_SIZE; ++i) {
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    for (int k = 0; k < MATRIX_SIZE; ++k) {
                        if (i < MATRIX_SIZE -1)
                            curl[i+isH][j][k][2] += mtx[i+1][j][k][1] - mtx[i][j][k][1];

                        if (j < MATRIX_SIZE - 1)
                            curl[i][j+isH][k][2] -= mtx[i][j+1][k][0] - mtx[i][j][k][0];
                    }
                }
            }
        };

        std::thread t1 (threadZ_1, std::ref(curl), mtx);
        std::thread t2 (threadZ_2, std::ref(curl), mtx);

        t1.join();
        t2.join();
    };
    
    std::thread tx (threadX, std::ref(curl), mtx);
    std::thread ty (threadY, std::ref(curl), mtx);
    std::thread tz (threadZ, std::ref(curl), mtx);

    tx.join();
    ty.join();
    tz.join();

    return curl;
}

void read_matrix(Matrix& mtx, const double* ptr)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                mtx[i][j][k][0] = ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 0];
                mtx[i][j][k][1] = ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 1];
                mtx[i][j][k][2] = ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 2];

            }
        }
    }
}

void write_matrix(const Matrix& mtx, double* ptr)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 0] = mtx[i][j][k][0];
                ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 1] = mtx[i][j][k][1];
                ptr[i * OFFSET_I + j * OFFSET_J + k * OFFSET_K + 2] = mtx[i][j][k][2];

            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error : no shared file provided as argv[1]" << std::endl;
        return -1;
    }

    wait_signal();

    // Création d'un fichier "vide" (le fichier doit exister et être d'une
    // taille suffisante avant d'utiliser mmap).
    memset(buffer_, 0, BUFFER_SIZE);
    FILE* shm_f = fopen(argv[1], "w");
    fwrite(buffer_, sizeof(char), BUFFER_SIZE, shm_f);
    fclose(shm_f);

    // On signale que le fichier est prêt.
    //std::cerr << "CPP:  File ready." << std::endl;
    ack_signal();

    // On ré-ouvre le fichier et le passe à mmap(...). Le fichier peut ensuite
    // être fermé sans problèmes (mmap y a toujours accès, jusqu'à munmap.)
    int shm_fd = open(argv[1], O_RDWR);
    void* shm_mmap = mmap(NULL, BUFFER_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    if (shm_mmap == MAP_FAILED) {
        std::cerr << "ERROR SHM\n";
        perror(NULL);
        return -1;
    }

    // Pointeur format double qui représente la matrice partagée:
    double* mtx = static_cast<double*>(shm_mmap);
    // Matrice
    Matrix new_mtx{100, std::vector<std::vector<std::array<double, 3>>>{100, std::vector<std::array<double, 3>>{100}}};
    
    

    while (true) {
        // On attend le signal du parent.
        wait_signal();
        read_matrix(new_mtx, mtx);
        Matrix newH = curl<H>(new_mtx);
        write_matrix(newH, mtx);
        ack_signal();

        wait_signal();
        read_matrix(new_mtx, mtx);
        Matrix newE = curl<E>(new_mtx);
        write_matrix(newE, mtx);
        ack_signal();


        // On signale que le travail est terminé.
        //std::cerr << "CPP: Work done." << std::endl;
    }

    munmap(shm_mmap, BUFFER_SIZE);
    return 0;
}