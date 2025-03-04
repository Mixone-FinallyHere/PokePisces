import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
from PIL import Image, ImageTk
import os
from FetchDataSheets import parse_pokemon_data

NEWLINE = '\n'
TYPE_COLORS = {
    "Fire": "#F08030", "Water": "#6890F0", "Grass": "#78C850",
    "Electric": "#F8D030", "Ice": "#98D8D8", "Fighting": "#C03028",
    "Poison": "#A040A0", "Ground": "#E0C068", "Flying": "#A890F0",
    "Psychic": "#F85888", "Bug": "#A8B820", "Rock": "#B8A038",
    "Ghost": "#705898", "Dragon": "#7038F8", "Dark": "#705848",
    "Steel": "#B8B8D0", "Fairy": "#EE99AC", "Normal": "#A8A878"
}

class PokemonApp:
    def __init__(self, root, pokemons, images_path):
        self.root = root
        self.root.title("Pokémon Viewer")
        self.root.geometry("900x800")  # Fixed window size
        
        self.pokemons = pokemons
        self.images_path = images_path
        self.current_index = 0        

        # Main container
        self.main_frame = tk.Frame(root)
        self.main_frame.pack(padx=10, pady=10, fill="both", expand=True)

        # Top section (Basic Info & Image)
        self.top_frame = tk.Frame(self.main_frame, bd=2, relief="groove")
        self.top_frame.pack(fill="x", padx=5, pady=5)

        self.info_frame = tk.LabelFrame(self.top_frame, text="Basic Info", padx=10, pady=5, width=250, height=150)
        self.info_frame.pack(side="left", anchor="nw", padx=10, pady=5, fill="both", expand=True)
        
        self.image_frame = tk.LabelFrame(self.top_frame, text="Pokémon Image", padx=10, pady=5, width=200, height=200)
        self.image_frame.pack(side="right", anchor="ne", padx=10, pady=5)
        
        self.pokemon_info_label = tk.Label(self.info_frame, text="", justify="left", font=("Arial", 12))
        self.pokemon_info_label.pack()
        
        self.pokemon_image_label = tk.Label(self.image_frame, width=200, height=200)
        self.pokemon_image_label.pack()
        
        # Middle Section
        self.middle_frame = tk.Frame(self.main_frame)
        self.middle_frame.pack(fill="x", pady=10)

        self.stats_frame = tk.LabelFrame(self.middle_frame, text="Stats", padx=10, pady=5, width=180, height=200)
        self.stats_frame.pack(side="left", padx=10, fill="y")

        self.evo_rarity_frame = tk.LabelFrame(self.middle_frame, text="Evolution & Rarity", padx=10, pady=5, width=180, height=200)
        self.evo_rarity_frame.pack(side="left", padx=10, fill="y")
        
        self.desc_frame = tk.LabelFrame(self.middle_frame, text="Description", padx=10, pady=5, width=200, height=200)
        self.desc_frame.pack(side="right", padx=10, fill="y")

        self.stats_label = tk.Label(self.stats_frame, text="", justify="left")
        self.stats_label.pack()

        self.evo_rarity_label = tk.Label(self.evo_rarity_frame, text="", justify="center")
        self.evo_rarity_label.pack()
        
        self.desc_label = tk.Label(self.desc_frame, text="", justify="left", wraplength=300)
        self.desc_label.pack()
        
        # Bottom Section
        self.bottom_frame = tk.LabelFrame(self.main_frame, text="Other Info", padx=10, pady=5, width=500)
        self.bottom_frame.pack(fill="x", pady=10)
        
        self.other_info_label = tk.Label(self.bottom_frame, text="", justify="left")
        self.other_info_label.pack()
        
        # Navigation & Selection
        self.nav_frame = tk.Frame(root)
        self.nav_frame.pack(pady=10)

        self.prev_button = tk.Button(self.nav_frame, text="Previous", command=self.show_previous_pokemon)
        self.prev_button.pack(side="left", padx=10)

        self.next_button = tk.Button(self.nav_frame, text="Next", command=self.show_next_pokemon)
        self.next_button.pack(side="left", padx=10)

        self.pokemon_names = [pokemon.name for pokemon in self.pokemons]
        self.selected_pokemon_var = tk.StringVar()
        self.selected_pokemon_var.set(self.pokemon_names[0])

        self.pokemon_dropdown = ttk.Combobox(root, values=self.pokemon_names, textvariable=self.selected_pokemon_var)
        self.pokemon_dropdown.pack(pady=10)
        self.pokemon_dropdown.bind("<<ComboboxSelected>>", self.on_pokemon_selected)

        # Show the first Pokémon
        self.update_pokemon_info()

    def update_pokemon_info(self):
        pokemon = self.pokemons[self.current_index]
        evo_methods = pokemon.evolution_method.split("+")
        evo_text = '\n- '.join(evo_methods)
        ability_text = '\n- '.join(pokemon.abilities)
        formatted_types = ' and '.join([f"{t}" for t in pokemon.types])

        self.pokemon_info_label.config(text=f"""
Dex ID: {pokemon.dexID}
Name: {pokemon.name}
Category: {pokemon.category}
Types: {formatted_types}
Abilities: 
- {ability_text}
""")
        
        self.stats_label.config(text=f"""
HP: {pokemon.hp}
Attack: {pokemon.atk}
Defense: {pokemon.def_stat}
Sp. Attack: {pokemon.spa}
Sp. Defense: {pokemon.spd}
Speed: {pokemon.spe}
BST: {pokemon.bst}
""")
        
        self.evo_rarity_label.config(text=f"""
Evolution Method: 
- {evo_text}
Rarity: 
{pokemon.rarity}
""")
        
        self.desc_label.config(text=f"{f'{NEWLINE}'.join(pokemon.dex_entry)}")
        
        self.other_info_label.config(text=f"""
Gender Ratio: {pokemon.gender_ratio}
Etymology: {pokemon.etymology}
Location: {pokemon.location}
EXP Yield: {pokemon.exp_yield}
Height: {pokemon.height} meters
Weight: {pokemon.weight} kg
Origin: {pokemon.origin}
""")
        
        self.display_pokemon_image(pokemon.dexID, pokemon.name)

    def display_pokemon_image(self, pokemon_id, pokemon_name):
        image_folder = str(pokemon_id) + pokemon_name.lower()
        image_path = os.path.join(self.images_path, image_folder, "front.png")
        if os.path.exists(image_path):
            image = Image.open(image_path).resize((200, 200))
            photo = ImageTk.PhotoImage(image)
            self.pokemon_image_label.config(image=photo)
            self.pokemon_image_label.image = photo
        else:
            self.pokemon_image_label.config(image="")
            self.pokemon_image_label.image = None

    def show_previous_pokemon(self):
        if self.current_index > 0:
            self.current_index -= 1
            self.update_pokemon_info()
            self.pokemon_dropdown.set(self.pokemons[self.current_index].name)
        else:
            messagebox.showinfo("End of List", "This is the first Pokémon.")

    def show_next_pokemon(self):
        if self.current_index < len(self.pokemons) - 1:
            self.current_index += 1
            self.update_pokemon_info()
            self.pokemon_dropdown.set(self.pokemons[self.current_index].name)
        else:
            messagebox.showinfo("End of List", "This is the last Pokémon.")

    def on_pokemon_selected(self, event):
        selected_pokemon_name = self.selected_pokemon_var.get()
        for index, pokemon in enumerate(self.pokemons):
            if pokemon.name == selected_pokemon_name:
                self.current_index = index
                self.update_pokemon_info()
                break



def run_app(file_path, images_path):
    pokemons = parse_pokemon_data(file_path)
    root = tk.Tk()
    app = PokemonApp(root, pokemons, images_path)
    root.mainloop()

file_path = 'PokemonPisces.xlsx'
images_path = '../graphics/pokemon'
run_app(file_path, images_path)
