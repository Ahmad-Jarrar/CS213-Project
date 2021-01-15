import pygame
import random
from abc import ABC
from itertools import zip_longest

from Ship import Ship
from animations import Smoke

class Board(ABC):
    def __init__(self, size, ship_sizes, cell_size, border_size, position):
        self.size = size
        self.ship_sizes = ship_sizes
        self.ships_list = []
        self.hits_list = []
        self.misses_list = []
        self.smokes = []
        self.cell_size = cell_size
        self.border_size = border_size
        self.surface = pygame.Surface((size * cell_size, size * cell_size))
        self.rect = pygame.Rect(position[0], position[1], size * cell_size, size * cell_size)
        self.ships_hidden = False
        self.random_initialize()

    def draw(self, screen):
        self.surface.fill(pygame.Color((43,118,187)))
        for y in range(self.size):
            for x in range(self.size):
                pygame.draw.rect(self.surface, pygame.Color(((53, 138, 217))),
                                     [x * self.cell_size + self.border_size,
                                      y * self.cell_size + self.border_size,
                                      self.cell_size - 2*self.border_size, 
                                      self.cell_size - 2*self.border_size])
        if not self.ships_hidden:
            for ship in self.ships_list:
                ship.draw(self.surface)

        for x,y in self.misses_list:
            pygame.draw.circle(self.surface, pygame.Color((8, 73, 119)), 
                                      [(x+0.5) * self.cell_size + self.border_size,
                                      (y+0.5) * self.cell_size + self.border_size], 
                                      3)

        for smoke in self.smokes:
            smoke.play_frame(self.surface)

        screen.blit(self.surface, self.rect)

    def clear(self):
        self.ships_list = []
        self.hits_list = []
        self.misses_list = []
        self.smokes = []

    def random_initialize(self):
        self.clear()
        for ship_length in self.ship_sizes:
            ship_added = False
            while not ship_added:
                x = random.randint(0, self.size - 1)
                y = random.randint(0, self.size - 1)
                ship_direction = random.randint(0,3)
                ship = Ship(x, y, ship_direction, ship_length, self.cell_size)
                if self.is_valid(ship):
                    self.add_ship(ship)
                    ship_added = True

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

    def valid_target(self, x, y):
        """Checks whether a set of coordinates is a valid shot
        Coordinates are within the board, and shot hasn't previously been taken
        """
        if x not in range(self.size) or y not in range(self.size):
            return False
        for previous_shot in self.misses_list + self.hits_list:
            if (x, y) == previous_shot:
                return False
        return True

    def shoot(self, x, y):
        """Registers a shot on the board, saving to appropriate list"""
        if not self.valid_target(x, y):
            return None

        for ship in self.ships_list:
            for ship_coordinate in ship.coordinate_list:
                if (x, y) == ship_coordinate:
                    self.hits_list.append((x, y))
                    self.smokes.append(Smoke(pygame.Rect(x * self.cell_size,
                                                        y * self.cell_size,
                                                        self.cell_size, 
                                                        self.cell_size)))
                    return 2

        self.misses_list.append((x, y))
        return 1

    def get_ship(self, x, y):
        """Gets a ship object from coordinates"""
        for ship in self.ships_list:
            if (x, y) in ship.coordinate_list:
                return ship
        return None
    
    def get_coordinates(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.display.quit()
                pygame.quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                if self.rect.collidepoint(x,y):
                    x = (x - self.rect.x) // self.cell_size
                    y = (y - self.rect.y) // self.cell_size
                    if x in range(self.size) and y in range(self.size):
                        return x, y, event.button
        return None, None, None

    @property
    def gameover(self):
        """Checks to see if all the ships have been fully hit"""
        for ship in self.ships_list:
            for coordinate in ship.coordinate_list:
                if coordinate not in self.hits_list:
                    return False
        return True

class PlayerBoard(Board):
    """A Board for user input"""

    def __init__(self, board_size, ship_sizes, cell_size, border_size, position):
        """Initialises the board by placing ships."""
        super().__init__(board_size, ship_sizes, cell_size, border_size, position)

        

    def populate(self, screen):
        direction = Ship.directions["NORTH"]
        while True:
            self.draw(screen)

            x, y, button = self.get_coordinates()
            if x is not None and y is not None:
                ship = self.get_ship(x, y)
                if ship:
                    self.remove_ship(ship)
                    if button == 3:
                        ship.rotate()
                        while not self.is_valid(ship):
                            ship.rotate()
                        self.add_ship(ship)
                elif self.ship_to_place:
                    if button == 1:
                        ship = Ship(x, y, direction, self.ship_to_place, self.cell_size)
                        if self.is_valid(ship):
                            self.add_ship(ship)
                        else:
                            direction = (direction + 1) % 4
                else:
                    break

                # if self.is_valid(ship):
                #     self.add_ship(ship)

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

    def __init__(self, board_size, ship_sizes, cell_size, border_size, position):
        """Initialises the board by randomly placing ships"""
        super().__init__(board_size, ship_sizes, cell_size, border_size, position)
        self.ships_hidden = True
        