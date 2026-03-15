import os
import glob

def rename_parameters():
    for root, dirs, files in os.walk('src/'):
        for file in files:
            if file == 'pokemon_parameters.txt':
                old_path = os.path.join(root, file)
                new_path = os.path.join(root, 'poke_parameters.txt')
                os.rename(old_path, new_path)
                with open(new_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                new_content = content.replace('pokemon', 'poke').replace('POKEMON', 'POKE').replace('Pokemon', 'Poke')
                with open(new_path, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                print(f"Renamed and updated {new_path}")

if __name__ == '__main__':
    rename_parameters()
