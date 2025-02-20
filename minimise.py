import pandas as pd

# Spécifier les noms des colonnes
column_names = ["Seuil", "TP", "FP", "TN", "FN", "Sensibilité", "Spécificité"]

# Charger les données du fichier
data = pd.read_csv('/home/mat/TPs_Image/metrics', sep=", ", engine='python', names=column_names, skiprows=1)

# Nettoyer les colonnes pour enlever les préfixes
data['TP'] = data['TP'].str.replace('TP: ', '').astype(int)
data['FP'] = data['FP'].str.replace('FP: ', '').astype(int)
data['TN'] = data['TN'].str.replace('TN: ', '').astype(int)
data['FN'] = data['FN'].str.replace('FN: ', '').astype(int)

# Trouver la ligne qui minimise la somme de FP et FN
min_fp_fn_row = data.loc[(data['FP'] + data['FN']).idxmin()]

# Calculer le Rappel, la Précision et le F1 score
TP = min_fp_fn_row['TP']
FP = min_fp_fn_row['FP']
FN = min_fp_fn_row['FN']

# Rappel (Sensibilité)
recall = TP / (TP + FN)

# Précision
precision = TP / (TP + FP)

# F1 score
f1_score = 2 * (precision * recall) / (precision + recall)

print(f"Ligne qui minimise FP et FN :\n{min_fp_fn_row}")
print(f"Rappel: {recall}")
print(f"Précision: {precision}")
print(f"F1 score: {f1_score}")