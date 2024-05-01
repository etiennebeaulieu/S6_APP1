#!/usr/bin/env python3

# GIF642 - Laboratoire 1 exercice 5
# Accède à un espace de mémoire partagé. Voir le fichier lab1_ex4.cpp associé.

import numpy as np
from subprocess import Popen, PIPE
import mmap
import time

def subp():
    subproc = Popen(["./lab_ex4", FNAME], stdin=PIPE, stdout=PIPE)
    return subproc

def signal_and_wait(subproc):
    subproc.stdin.write("START\n".encode())
    subproc.stdin.flush()                   # Nécessaire pour vider le tampon de sortie
    res = subproc.stdout.readline()
    #print(res)

FNAME       = "GIF642-labo-shm"
MATRIX_SIZE = 4

# Lancement de l'exécutable associé
# NOTE: suppose que l'exécutable est dans le même dossier que celui en cours (normalement build/)
subproc = subp()

# Envoi d'une ligne sur l'entrée du sous-processus et attend un retour pour signaler que
# nous sommes prêts à passer à la prochaine étape. 
signal_and_wait(subproc)

shm_f = open(FNAME, "r+b")
shm_mm = mmap.mmap(shm_f.fileno(), 0)

shared_matrix = np.ndarray(shape=(MATRIX_SIZE, MATRIX_SIZE), dtype=np.float64, buffer=shm_mm)
shared_matrix[:] = [[1,2,3,4], [5,6,7,8], [9,10,11,12], [13,14,15,16]]
print("PY:  Initial matrix:")
print(shared_matrix)

for i in range(0,10):
    signal_and_wait(subproc)
    print("PY:  Result:")
    print(shared_matrix)

# Test rapide : La case (3,2) (rangée 3, colonne 2, indexé à 0) devrait être égale à 25 (15+10):
if (shared_matrix[3,2] != 25.0):
    print("PY:  Error! matrix[3,2] is", shared_matrix[3,2], "should be 25.0")

print("PY:  Done")

subproc.kill()
shm_mm.close()