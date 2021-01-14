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
        self.window_size = [2 * board_size * cell_size + margin, board_size * cell_size + margin + 200]
        self.screen = pygame.display.set_mode(self.window_size)
        pygame.display.set_caption("Battleships")
        self.screen.fill(pygame.Color(236,240,241))

        self.pboard = PlayerBoard(self.screen, board_size, ship_sizes, cell_size, 0.3)

    def play(self):
        while not self.game_over:
            self.get_input()
            self.screen.fill(pygame.Color(236,240,241))
            # self.board.draw(self.screen)
            pygame.display.flip()
            pygame.time.Clock().tick(60)
            print("everything ok")


    def get_input(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.display.quit()
                pygame.quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                x = x % (self.board_size * self.cell_size + self.margin)
                x = (x - self.margin) // self.cell_size
                y = (y - self.margin) // self.cell_size
                if x in range(self.board_size) and y in range(self.board_size):
                    return x, y
        return None, None

    # TODO: Game over logic
    @property
    def game_over(self):
        return False

    

if __name__ == "__main__":
    while True:
        Game().play()
        response = input("Replay? y/n: ").lower()
        while response not in ['y', 'n']:
            response = input("Must be y or n: ")
        if response == 'n':
            print("Thanks, goodbye.")
            break
