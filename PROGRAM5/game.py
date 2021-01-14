import pygame
import random
from abc import ABC
from enum import Enum
from Board import PlayerBoard
from itertools import zip_longest

class Game():
    def __init__(self, board_size=8, cell_size=40, margin=1, ship_sizes=[4, 3, 3, 2, 2, 2]):
        pygame.init()
        self.board_size = board_size
        self.cell_size = cell_size
        self.margin = margin
        self.ship_sizes = ship_sizes
        self.window_size = [board_size * cell_size + margin, 2 * board_size * cell_size + margin]
        self.screen = pygame.display.set_mode(self.window_size)
        pygame.display.set_caption("Battleships")
        self.board = PlayerBoard(self.screen, board_size, ship_sizes, cell_size, 1)

    def play(self):
        while True:
            self.board.draw(self.screen)
            self.screen.update()


if __name__ == "__main__":
    while True:
        Game().play()
        # Game(d, 2, [1,1]).play()

        response = input("Replay? y/n: ").lower()
        while response not in ['y', 'n']:
            response = input("Must be y or n: ")
        if response == 'n':
            print("Thanks, goodbye.")
            break
