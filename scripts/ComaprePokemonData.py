# compare_pokemon.py
from FetchDataSheets import parse_pokemon_data
from FetchDataSrc import parse_species_info
from typing import List

ABILITY_RENAMES = {
    "Bass Boost": "Punk Rock",
    "Alchemist": "Power Of Alchemy",
    "Sand Compact": "Water Compaction",
    "Checkmate": "Supreme Overlord",
    "Squeaky Clean": "Good As Gold",
    "Resolute": "Intrepid Sword",
    "Baked Body": "Well Baked Body",
    "Dauntless": "Dauntless Shield",
    "Fragile": "Ice Face",
    "Majesty": "Queenly Majesty",
    "Heat Transfer": "Thermal Exchange",
    "Electromorph": "Electromorphosis",
    "Eggs Royale": "Tera Shell"
}

def compare_attribute(attr_name, value1, value2, mismatches, species_name):
    """Helper function to compare attributes and log mismatches."""
    if value1 != value2:
        if species_name not in mismatches:
            mismatches[species_name] = []
        mismatches[species_name].append(f"Mismatch for {attr_name}: {value1} (sheet) != {value2} (species_info)")

def compare_pokemon_data(pokemons, pokemon_data):
    mismatches = {}

    for pokemon in pokemons:
        # Retrieve the corresponding species from pokemon_data (case-insensitive comparison)
        species_name = pokemon.name.upper()
        if species_name not in pokemon_data:
            #mismatches.append(f"{species_name} not found in species data.")
            continue

        species_info = pokemon_data[species_name]

        # Compare basic stats (hp, attack, defense, etc.)
        compare_attribute("base_hp", pokemon.hp, species_info.base_hp, mismatches, species_name)
        compare_attribute("base_attack", pokemon.atk, species_info.base_attack, mismatches, species_name)
        compare_attribute("base_defense", pokemon.def_stat, species_info.base_defense, mismatches, species_name)
        compare_attribute("base_speed", pokemon.spe, species_info.base_speed, mismatches, species_name)
        compare_attribute("base_sp_attack", pokemon.spa, species_info.base_sp_attack, mismatches, species_name)
        compare_attribute("base_sp_defense", pokemon.spd, species_info.base_sp_defense, mismatches, species_name)

        # Compare types
        for i, p_type in enumerate(pokemon.types):
            if i < len(species_info.types) and p_type not in species_info.types:
                if species_name not in mismatches:
                    mismatches[species_name] = []
                mismatches[species_name].append(f"Mismatch for types: {pokemon.types} (sheet) != {species_info.types} (species_info)")

        # Compare other attributes (catch_rate, exp_yield, abilities, etc.)
        #compare_attribute("catch_rate", pokemon.uses, species_info.catch_rate, mismatches, species_name)
        compare_attribute("exp_yield", pokemon.exp_yield, species_info.exp_yield, mismatches, species_name)

        # Compare abilities (abilities are a list)
        for ability in pokemon.abilities:
            if ability in ABILITY_RENAMES:
                ability_clean = ABILITY_RENAMES[ability]
            else:
                ability_clean = ability
            if len(species_info.abilities) < 3:
                if species_name not in mismatches:
                    mismatches[species_name] = []
                mismatches[species_name].append(f"Only 2 abilities set in source code! => {species_info.abilities}")
            if ability not in species_info.abilities and ability_clean not in species_info.abilities:
                if species_name not in mismatches:
                    mismatches[species_name] = []
                mismatches[species_name].append(f"Mismatch for abilities: {ability_clean} or {ability} (sheet) not in {species_info.abilities} (species_info)")

        # Compare other possible attributes if needed (gender_ratio, egg_groups, etc.)
        #compare_attribute("gender_ratio", pokemon.gender_ratio, species_info.gender_ratio, mismatches, species_name)
        #compare_attribute("egg_cycles", pokemon.egg_cycles, species_info.egg_cycles, mismatches, species_name)
        #compare_attribute("growth_rate", pokemon.growth_rate, species_info.growth_rate, mismatches, species_name)
        #compare_attribute("egg_groups", pokemon.location, species_info.egg_groups, mismatches, species_name)
        #compare_attribute("body_color", pokemon.body_color, species_info.body_color, mismatches, species_name)
        #compare_attribute("no_flip", pokemon.rarity, species_info.no_flip, mismatches, species_name)

    return mismatches

if __name__ == "__main__":
    # Load the Pokémon data from the Excel sheet (or wherever it comes from)
    file_path = 'PokemonPisces.xlsx'
    pokemons = parse_pokemon_data(file_path)

    # Load Pokémon names from the FetchDataSheets data
    pokemon_names = [pokemon.name.upper() for pokemon in pokemons]

    # Load the species info from the 'species_info.h' file
    species_info_path = '../src/data/pokemon/species_info.h'
    pokemon_data = parse_species_info(species_info_path, pokemon_names)

    # Compare the data and display mismatches
    mismatches = compare_pokemon_data(pokemons, pokemon_data)

    if mismatches:
        for species, mismatched in mismatches.items():
            print(f"Mismatches for {species}:")
            for mismatch in mismatched:
                print("\t"+mismatch)
            print()
    else:
        print("No mismatches found.")
