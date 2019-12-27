# Projet-Pharma

Stage de 2 mois éffectué du 21/10/2019 au 27/12/2019

Projet réalisé à l'aide du framework qt et du logiciel associé Qt Creator (lien : https://www.qt.io/)

Ce logiciel à pour fonction de gérer un plannificateur pour remplir des pilulier à partir d'une ordonnance et permet la gestion des fichier de données (patients, groupe/secteur, médecins).
Il permet aussi la saisie d'ordonnance ainsi que la comparaison avec les précédentes ordonnances.
Reste à faire la blistérisation et les éditions de bordereaux.

Description des fichiers :

-main.cpp : fonction main.
-mainwindow : fenêtre principale.
-centralwidgetordonnance : widget central.
-tablemodel : model custom de la view secteur.
-tablemodelhistory : model custom de la view de l'historique d'ordonnance.
-tablemodelordo : model custom de la view de l'ordonnance en cours d'édition.
-tablemodelpatient : model custom de la view patient.
-windowviewgroupe : fenêtre d'édition de groupe.
-windowviewmedecin : fenêtre d'édition de médecin.
-windowviewpatient : fenêtre d'édition de patient.
-windowviewproduit : fenêtre affichant la liste des produits.
-windowviewsecteur : fenêtre d'ajout/suppression de secteur.
-lineeditproduitdelegate.h : delegate permettant l'ajout d'un QCompleter dans la colonne produit de l'ordonnance en cours.
-ComboBoxFrequenceDelegate : delegate permettant l'ajout d'un QComboBox dans la colonne fréquence de l'historique d'ordonnance.
