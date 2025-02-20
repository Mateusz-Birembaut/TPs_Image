import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

# Lire les données et les nettoyer
data = []
with open('resultats.csv', 'r') as f:
    next(f)  # Ignorer l'en-tête
    for line in f:
        if 'PNSR' in line:  # Ligne contenant le PSNR
            psnr = float(line.split(':')[1].split('dB')[0])
            data[-1].append(psnr)
        else:  # Ligne contenant les autres données
            parts = line.strip().split(',')
            if len(parts) >= 6:  # Vérifier qu'il y a assez de colonnes
                niveau = int(parts[0])
                bpp = float(parts[5])
                data.append([niveau, bpp])

# Convertir en DataFrame
df = pd.DataFrame(data, columns=['Niveau', 'BPP', 'PSNR'])

# Tracer une courbe pour chaque niveau
plt.figure(figsize=(10, 6))
for niveau in df['Niveau'].unique():
    niveau_data = df[df['Niveau'] == niveau]
    plt.plot(niveau_data['BPP'], niveau_data['PSNR'], 
             marker='o', label=f'Niveau {niveau}')

plt.xlabel('Débit (bpp)')
plt.ylabel('PSNR (dB)')
plt.title('Courbes débit/distorsion pour différents niveaux')
plt.legend(title='Niveaux de décomposition', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True)
plt.tight_layout()
plt.savefig('debit_distorsion.png', dpi=300, bbox_inches='tight')
plt.close()