import pygame
import random
from Board import PlayerBoard, AIBoard

class Game():
    def __init__(self, board_size=8, cell_size=40, margin=20, ship_sizes=[4, 3, 3, 2, 2, 2]):
        pygame.init()
        self.board_size = board_size
        self.cell_size = cell_size
        self.margin = margin
        self.ship_sizes = ship_sizes

        self.subwindow_positions = {
            "AI Board": [self.margin, self.margin],
            "Player Board": [2*self.margin + board_size*cell_size, self.margin],
            "Menu": [self.margin, 2*self.margin + board_size*cell_size]
        }


        self.window_size = [2 * board_size * cell_size + 3*margin, board_size * cell_size + 2*margin + 200]
        self.screen = pygame.display.set_mode(self.window_size)
        pygame.display.set_caption("Battleships")
        self.screen.fill(pygame.Color(236,240,241))

        self.pboard = PlayerBoard(board_size, ship_sizes, cell_size, 0.3, self.subwindow_positions["Player Board"])
        self.pboard.populate(self.screen)
        self.aiboard = AIBoard(board_size, ship_sizes, cell_size, 0.3, self.subwindow_positions["AI Board"])

    def play(self):
        while not self.game_over:
            if self.player_turn():
                self.ai_turn()

            self.screen.fill(pygame.Color(236,240,241))
            self.aiboard.draw(self.screen)
            self.pboard.draw(self.screen)
            
            pygame.display.flip()
            pygame.time.Clock().tick(60)
            
    def player_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y = self.aiboard.get_coordinates()
        if self.aiboard.valid_target(x, y):
            result = self.aiboard.shoot(x, y)
            # animate
            return True
        else:
            return False

    def ai_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y = -1, -1
        while not self.pboard.valid_target(x, y):
            x = random.randint(0, self.board_size - 1)
            y = random.randint(0, self.board_size - 1)
        
        if self.aiboard.valid_target(x, y):
            result = self.pboard.shoot(x, y)
            # animate
            return True
        else:
            return False

    # def get_input(self):
    #     for event in pygame.event.get():
    #         if event.type == pygame.QUIT:
    #             pygame.display.quit()
    #             pygame.quit()
    #         elif event.type == pygame.MOUSEBUTTONDOWN:
    #             x, y = pygame.mouse.get_pos()
    #             x = x % (self.board_size * self.cell_size + self.margin)
    #             x = (x - self.margin) // self.cell_size
    #             y = (y - self.margin) // self.cell_size
    #             if x in range(self.board_size) and y in range(self.board_size):
    #                 return x, y
    #     return None, None

    # TODO: Game over logic
    @property
    def game_over(self):
        """Determines and prints the winner"""
        if self.aiboard.gameover:
            print("Congratulations you won")
            return True
        elif self.pboard.gameover:
            print("Congratulations you lost")
            return True
        else:
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
