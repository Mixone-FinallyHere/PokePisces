from math import floor
import pandas as pd

class Pokemon:
    def __init__(self, dexID, name, uses, category, types, abilities, hp, atk, def_stat, spa, spd, spe, bst, evolution_method, rarity, dex_entry, gender_ratio, etymology, location, exp_yield, height, weight, origin):
        self.dexID = dexID
        self.name = name
        self.uses = uses
        self.category = category
        self.types = [type for type in types if type != 'None']
        self.abilities = abilities
        self.hp = int(hp) if hp != 'None' else 0
        self.atk = int(atk) if atk != 'None' else 0
        self.def_stat = int(def_stat) if def_stat != 'None' else 0
        self.spa = int(spa) if spa != 'None' else 0
        self.spd = int(spd) if spd != 'None' else 0
        self.spe = int(spe) if spe != 'None' else 0
        self.bst = int(bst) if bst != 'None' else 0
        self.evolution_method = evolution_method
        self.rarity = rarity
        self.dex_entry = dex_entry
        self.gender_ratio = gender_ratio
        self.etymology = etymology
        self.location = location
        self.exp_yield = floor(float(exp_yield) + 0.5) if exp_yield != 'None' else 0
        self.height = float(height) if height != 'None' else 0.0
        self.weight = float(weight) if weight != 'None' else 0.0
        self.origin = origin
    
    def __repr__(self):
        # Format stats for readability
        stats = f"""
        Dex ID: {self.dexID}
        Name: {self.name}
        Category: {self.category}
        Types: {' and '.join(self.types)}
        Abilities: {' / '.join(self.abilities)}

        Stats:
        - HP: {self.hp}
        - Attack: {self.atk}
        - Defense: {self.def_stat}
        - Special Attack: {self.spa}
        - Special Defense: {self.spd}
        - Speed: {self.spe}
        - BST (Base Stat Total): {self.bst}

        Evolution Method: {self.evolution_method}
        Rarity: {self.rarity}

        Description:
        {" ".join(self.dex_entry)}

        Other Info:
        - Gender Ratio (M:F): {self.gender_ratio}
        - Etymology: {self.etymology}
        - Location: {self.location}
        - EXP Yield: {self.exp_yield}
        - Height: {self.height} meters
        - Weight: {self.weight} kg
        - Origin: {self.origin}
        """
        return stats.strip()

def parse_pokemon_data(file_path):
    # Load the Excel file using pandas
    df = pd.read_excel(file_path)
    df = df.fillna('None')  # Replace NaN with 'None' to handle missing values.
    
    # List to hold all Pokemon objects
    pokemons = []
    current_dexID = 1
    # Iterate through each row of the dataframe
    for _, row in df.iterrows():
        # Create a Pokemon object from each row and append it to the list
        pokemon = Pokemon(
            dexID=current_dexID,
            name=row['Name:'],
            uses=row['Uses:'],
            category=row['Category:'],
            types=(row.iloc[9], row.iloc[10]),
            abilities=row['Abilities:'].replace("*", "").replace("^", "").replace("'", "").replace("-", " ").split("\n"),
            hp=row['HP'],
            atk=row['ATK'],
            def_stat=row['DEF'],
            spa=row['SPA'],
            spd=row['SPD'],
            spe=row['SPE'],
            bst=row['BST'],
            evolution_method=row['Evolution Method:'],
            rarity=row['Rarity:'],
            dex_entry=row['Dex Entry:'].split("\n"),
            gender_ratio=row['Gender Ratio (M:F):'],
            etymology=row['Etymology:'],
            location=row['Location:'],
            exp_yield=row['EXP. Yield'],
            height=row['Height (Meters)'],
            weight=row['Weight (Kilograms):'],
            origin=row['Origin:']
        )
        pokemons.append(pokemon)
        current_dexID += 1

    return pokemons

if __name__ == "__main__":
    file_path = 'PokemonPisces.xlsx'
    pokemons = parse_pokemon_data(file_path)
