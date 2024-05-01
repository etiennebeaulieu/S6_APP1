#!/usr/bin/env python3
# S6 APP1 - Labo 1, exercice 5

import numpy as np

# Quelques exercices avec l'indexation numpy
# Les réponses doivent être dans les variables qX, et les réponses attendues 
# sont dans les variables qX_rep.
# Les réponses doivent être des sous-ensembles des tableaux data1D, 2D ou 3D.
# Modifiez les lignes qX = dataXD[:] pour obtenir les réponses attendues.
# La réponse par défaut retourne tous les éléments.
# La fonction test prend l'ensemble des réponses et vous donnent votre résultat.
# Tout est automatique, vous n'avez rien à changer au programme à part ces lignes.

def test(qs, rs):
    pairs = zip(qs, rs)
    i = 0
    for (q, r) in pairs:
        i += 1
        if not np.array_equal(q, r):
            print("Erreur q%i: %s devrait être %s."%(i, str(q), str(r)))

data1D = np.array([1,2,3,4,5])      # Vecteur 1x5
data2D = np.array([                 # Matrice 5x5
    [1,2,3,4,5],
    [6,7,8,9,10],
    [11,12,13,14,15],
    [16,17,18,19,20],
    [21,22,23,24,25]
])
data3D = np.array([                 # Cube 2x2x2
    [[1,2], [3,4]],                 # Première couche 2x2
    [[5,6], [7,8]]                  # Deuxième couche 2x2
])

### QUESTIONS ###

# Q1 - Tous les éléments du vecteur 1D (la réponse est donnée)
q1      = data1D[:] 
q1_rep  = data1D

# Q2 - Les trois premiers éléments du vecteur 1D
q2      = data1D[:3]
q2_rep  = np.array([1,2,3])

# Q3 - Les deux derniers éléments du vecteur 1D
q3      = data1D[-2:]
q3_rep  = np.array([4,5])

# Q4 - L'élément (2,3) de la matrice 2D (attention: 1 est le premier élément)
q4      = data2D[1, 2]
q4_rep  = 8

# Q5 - La dernière colonne de la matrice 2D, en utilisant un indice négatif
q5      = data2D[:,-1]
q5_rep  = np.array([5, 10, 15, 20, 25])

# Q6 - La couche inférieure du cube 2x2x2
q6      = data3D[-1,:]
q6_rep  = np.array([[5,6], [7,8]])

# Q7 - Dans la première rangée de la matrice 2D, la soustraction des éléments 2-5 et 1-4,
#      donc (2,3,4,5) - (1,2,3,4) = (1,1,1,1)
q7      = data2D[0,-4:] - data2D[0,:4]
q7_rep  = np.array([1,1,1,1])

### VÉRIFICATION ###

qs = [q1,q2,q3,q4,q5,q6,q7]
rs = [q1_rep, q2_rep, q3_rep, q4_rep, q5_rep, q6_rep, q7_rep]
test(qs, rs)