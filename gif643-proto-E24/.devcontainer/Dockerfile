# Utilisation de Debian Bookworm comme image de base
FROM debian:bookworm

# Éviter les avertissements d'apt-get
ENV DEBIAN_FRONTEND=noninteractive

# Création de l'utilisateur non-root
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Mise à jour des dépôts et installation des packages essentiels, y compris python3-venv
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog \
    && apt-get -y install git iproute2 procps lsb-release \
    && apt-get -y install build-essential cmake cppcheck valgrind strace \
    && apt-get -y install python3-dev python3-tk python3-pip python3-venv \
    && groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Créez un environnement virtuel Python et installez des packages dans cet environnement
USER $USERNAME
WORKDIR /workspace

# Créer un environnement virtuel Python
RUN python3 -m venv /workspace/venv \
    && . /workspace/venv/bin/activate \
    && pip install --upgrade pip \
    && pip install Cython numpy
