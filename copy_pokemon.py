import os
import shutil
import glob

def main():
    base_dir = '/home/sinofine/poke/src'
    # Find all poke_lvl* directories
    for root, dirs, files in os.walk(base_dir):
        for dirname in list(dirs):
            if dirname.startswith('poke_lvl'):
                src_path = os.path.join(root, dirname)
                
                # We need to create pokemon_lvlX
                lvl_part = dirname.replace('poke_', '')
                new_dirname = f'pokemon_{lvl_part}'
                dst_path = os.path.join(root, new_dirname)
                
                print(f"Copying {src_path} to {dst_path}")
                if os.path.exists(dst_path):
                    shutil.rmtree(dst_path)
                shutil.copytree(src_path, dst_path)
                
                # Now rename inner files and dirs
                for new_root, new_dirs, new_files in os.walk(dst_path, topdown=False):
                    for name in new_files:
                        if 'poke' in name or 'POKE' in name or 'Poke' in name:
                            new_name = name.replace('poke', 'pokemon').replace('POKE', 'POKEMON').replace('Poke', 'Pokemon')
                            os.rename(os.path.join(new_root, name), os.path.join(new_root, new_name))
                    for name in new_dirs:
                        if 'poke' in name or 'POKE' in name or 'Poke' in name:
                            new_name = name.replace('poke', 'pokemon').replace('POKE', 'POKEMON').replace('Poke', 'Pokemon')
                            os.rename(os.path.join(new_root, name), os.path.join(new_root, new_name))
                            
                # Now rewrite contents
                for new_root, new_dirs, new_files in os.walk(dst_path):
                    for name in new_files:
                        file_path = os.path.join(new_root, name)
                        try:
                            with open(file_path, 'r', encoding='utf-8') as f:
                                content = f.read()
                            new_content = content.replace('poke', 'pokemon').replace('POKE', 'POKEMON').replace('Poke', 'Pokemon')
                            if content != new_content:
                                with open(file_path, 'w', encoding='utf-8') as f:
                                    f.write(new_content)
                        except UnicodeDecodeError:
                            pass # skip binary files

if __name__ == '__main__':
    main()
