import pygame
import random
from abc import ABC
from Ship import Ship
from itertools import zip_longest

class Board(ABC):
    def __init__(self, size, ship_sizes, cell_size, border_size):
        self.size = size
        self.ship_sizes = ship_sizes
        self.ships_list = []
        self.hits_list = []
        self.misses_list = []
        self.cell_size = cell_size
        self.border_size = border_size
        self.surface = pygame.Surface((size[0] * cell_size, size[1] * cell_size))

    def draw(self, screen):
        self.surface.fill(pygame.Color((43, 118, 187)))
        screen.blit(self.surface)

    def is_valid(self, ship):
        """Checks whether a ship would be a valid placement on the board"""
        for x, y in ship.coordinate_list:
            if x < 0 or y < 0 or x >= self.size or y >= self.size:
                return False
        for otherShip in self.ships_list:
            if self.ships_overlap(ship, otherShip):
                return False
        return True

    def add_ship(self, ship: Ship):
        """Adds a ship to the board"""
        if self.is_valid(ship):
            self.ships_list.append(ship)
            return True
        else:
            return False

    def remove_ship(self, ship):
        """Removes a ship from the board"""
        self.ships_list.remove(ship)

    def ships_overlap(self, ship1, ship2):
        """Checks whether two ships overlap"""
        for ship1_coord in ship1.coordinate_list:
            for ship2_coord in ship2.coordinate_list:
                if ship1_coord == ship2_coord:
                    return True
        return False

    def get_ship(self, x, y):
        """Gets a ship object from coordinates"""
        for ship in self.ships_list:
            if (x, y) in ship.coordinate_list:
                return ship
        return None

class PlayerBoard(Board):
    """A Board for user input"""

    def __init__(self, display, board_size, ship_sizes, cell_size, border_size):
        """Initialises the board by placing ships."""
        super().__init__(board_size, ship_sizes, cell_size, border_size)
        self.display = display

        direction = Ship.directions["NORTH"]
        while True:
            self.display.show(None, self)

            if self.ship_to_place:
                text = 'Click where you want your {}-long ship to be:'.format(
                    self.ship_to_place)
            else:
                text = 'Click again to rotate a ship, or elsewhere if ready.'
            self.display.show_text(text, lower=True)

            x, y = self.display.get_input()
            if x is not None and y is not None:
                ship = self.get_ship(x, y)
                if ship:
                    self.remove_ship(ship)
                    ship.rotate()
                    if self.is_valid(ship):
                        self.add_ship(ship)
                elif self.ship_to_place:
                    ship = Ship(x, y, direction, self.ship_to_place, cell_size)
                    if self.is_valid(ship):
                        self.add_ship(ship)
                    else:
                        direction = (direction + 1) % 4
                else:
                    break

                if self.is_valid(ship):
                    self.add_ship(ship)

            pygame.display.flip()
            pygame.time.Clock().tick(60)

    @property
    def ship_to_place(self):
        """Returns a ship length that needs to be placed, if any"""
        placed_sizes = sorted(ship.length for ship in self.ships_list)
        sizes = sorted(self.ship_sizes)
        for placed, to_place in zip_longest(placed_sizes, sizes):
            if placed != to_place:
                return to_place
        return None


class AIBoard(Board):
    """A Board controlled by a AI"""

    def __init__(self, board_size, ship_sizes, cell_size, border_size):
        """Initialises the board by randomly placing ships"""
        super().__init__(board_size, ship_sizes, cell_size, border_size)
        for ship_length in self.ship_sizes:
            ship_added = False
            while not ship_added:
                x = random.randint(0, board_size - 1)
                y = random.randint(0, board_size - 1)
                ship_direction = random.choice(Ship.directions.values)
                ship = Ship(x, y, ship_direction, ship_length, cell_size)
                if self.is_valid(ship):
                    self.add_ship(ship)
                    ship_added = True