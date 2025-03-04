import re
from typing import List
from FetchDataSheets import parse_pokemon_data
class PokemonSrc:
    def __init__(self, species_name: str, base_hp: int, base_attack: int, base_defense: int, base_speed: int,
                 base_sp_attack: int, base_sp_defense: int, types: list, catch_rate: int, exp_yield: int,
                 ev_yield_sp_attack: int, ev_yield_sp_defense: int, gender_ratio: str, egg_cycles: int,
                 friendship: str, growth_rate: str, egg_groups: list, abilities: list,
                 body_color: str, no_flip: bool):
        self.species_name = species_name
        self.base_hp = base_hp
        self.base_attack = base_attack
        self.base_defense = base_defense
        self.base_speed = base_speed
        self.base_sp_attack = base_sp_attack
        self.base_sp_defense = base_sp_defense
        self.types = types
        self.catch_rate = catch_rate
        self.exp_yield = exp_yield
        self.ev_yield_sp_attack = ev_yield_sp_attack
        self.ev_yield_sp_defense = ev_yield_sp_defense
        self.gender_ratio = gender_ratio
        self.egg_cycles = egg_cycles
        self.friendship = friendship
        self.growth_rate = growth_rate
        self.egg_groups = egg_groups
        self.abilities = abilities
        self.body_color = body_color
        self.no_flip = no_flip

def extract_pokemon_names_from_data(pokemons):
    # Extract a list of Pokémon names
    return [pokemon.name.upper() for pokemon in pokemons]

def parse_species_info(file_path, species_names):
    species_info = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Start parsing from the line that begins with 'const struct SpeciesInfo gSpeciesInfo[] ='
    is_parsing = False
    species_name = ''
    species_data = {}

    for line in lines:
        # Start of the species info array
        if line.strip().startswith('const struct SpeciesInfo gSpeciesInfo[]'):
            is_parsing = True
            continue  # Skip this line

        if is_parsing:
            # Skip empty lines or non-data lines
            line = line.strip()
            if not line or line.startswith('};'):
                continue

            # If a species entry starts with a bracket like [SPECIES_BULBASAUR]
            if line.startswith('['):
                # If we're already parsing a species, save the previous one
                if species_name and species_data:
                    if species_name in species_names:
                        # Only add species that are in the species_names list
                        species_info[species_name] = PokemonSrc(
                            species_name,
                            species_data.get('baseHP', 0),
                            species_data.get('baseAttack', 0),
                            species_data.get('baseDefense', 0),
                            species_data.get('baseSpeed', 0),
                            species_data.get('baseSpAttack', 0),
                            species_data.get('baseSpDefense', 0),
                            species_data.get('types', []),
                            species_data.get('catchRate', 0),
                            species_data.get('expYield', 0),
                            species_data.get('evYield_SpAttack', 0),
                            species_data.get('evYield_SpDefense', 0),
                            species_data.get('genderRatio', ''),
                            species_data.get('eggCycles', 0),
                            species_data.get('friendship', ''),
                            species_data.get('growthRate', ''),
                            species_data.get('eggGroups', []),
                            species_data.get('abilities', []),
                            species_data.get('bodyColor', ''),
                            species_data.get('noFlip', False)
                        )
                    species_data = {}

                # Extract species name from the line [SPECIES_X]
                species_name = line.split(']')[0].replace('[SPECIES_', '').strip()
                continue

            # Parse the data for each species
            if line.startswith('.'):
                # Extract the property and value
                if '.baseHP' in line:
                    species_data['baseHP'] = int(line.split('=')[1].strip().strip(','))
                elif '.baseAttack' in line:
                    species_data['baseAttack'] = int(line.split('=')[1].strip().strip(','))
                elif '.baseDefense' in line:
                    species_data['baseDefense'] = int(line.split('=')[1].strip().strip(','))
                elif '.baseSpeed' in line:
                    species_data['baseSpeed'] = int(line.split('=')[1].strip().strip(','))
                elif '.baseSpAttack' in line:
                    species_data['baseSpAttack'] = int(line.split('=')[1].strip().strip(','))
                elif '.baseSpDefense' in line:
                    species_data['baseSpDefense'] = int(line.split('=')[1].strip().strip(','))
                elif '.types' in line:
                    species_data['types'] = [t.replace('TYPE_', '').replace("}", "").replace("_", " ").lower().title().strip() for t in line.split('=')[1].strip().strip('{}').split(',')]
                elif '.catchRate' in line:
                    species_data['catchRate'] = int(line.split('=')[1].strip().strip(','))
                elif '.expYield' in line:
                    species_data['expYield'] = int(line.split('=')[1].strip().strip(','))
                elif '.evYield_SpAttack' in line:
                    species_data['evYield_SpAttack'] = int(line.split('=')[1].strip().strip(','))
                elif '.evYield_SpDefense' in line:
                    species_data['evYield_SpDefense'] = int(line.split('=')[1].strip().strip(','))
                elif '.genderRatio' in line:
                    species_data['genderRatio'] = line.split('=')[1].strip().strip(',')
                elif '.eggCycles' in line:
                    species_data['eggCycles'] = int(line.split('=')[1].strip().strip(','))
                elif '.friendship' in line:
                    species_data['friendship'] = line.split('=')[1].strip().strip(',')
                elif '.growthRate' in line:
                    species_data['growthRate'] = line.split('=')[1].strip().strip(',')
                elif '.eggGroups' in line:
                    species_data['eggGroups'] = [e.strip() for e in line.split('=')[1].strip().strip('{}').split(',')]
                elif '.abilities' in line:
                    species_data['abilities'] = [a.replace('ABILITY_', '').replace("}", "").replace("_", " ").lower().title().strip() for a in line.split('=')[1].strip().strip('{}').split(',') if a != ""]
                elif '.bodyColor' in line:
                    species_data['bodyColor'] = line.split('=')[1].strip().strip(',')
                elif '.noFlip' in line:
                    species_data['noFlip'] = True if line.split('=')[1].strip().strip(',') == 'TRUE' else False

    return species_info


if __name__ == "__main__":
    file_path = 'PokemonPisces.xlsx'
    pokemons = parse_pokemon_data(file_path)

    # Example of loading the file and parsing it
    file_path = '../src/data/pokemon/species_info.h'

    # Load Pokémon names from the FetchDataSheets data
    pokemon_names = extract_pokemon_names_from_data(pokemons)

    # Parse species info based on the filtered list of names
    pokemon_data = parse_species_info(file_path, pokemon_names)

    print("\n".join([poke for poke in pokemon_data]))

