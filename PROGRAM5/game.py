import pygame
import pygame_menu
from Board import PlayerBoard, AIBoard
from animations import Explosion, Ripple, Background
from AI.AImove import aiTurn

class Game():
    
    def __init__(self, board_size=8, cell_size=50, margin=20, border_size=0.3, ship_types=["Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"]):
        pygame.init()
        pygame.mixer.init()
        self.previous_win = False
        self.replay = False
        self.board_size = board_size
        self.cell_size = cell_size
        self.margin = margin
        self.border_size = border_size
        self.ship_types_list = ship_types
        self.subwindow_positions = {
            "AI Board": [self.margin, self.margin + 50],
            "Player Board": [2*self.margin + board_size*cell_size, self.margin + 50],
            "Menu": [self.margin, 2*self.margin + board_size*cell_size + 50]
        }


        self.menu_theme = pygame_menu.themes.Theme(
                            surface_clear_color=(173, 200, 216),
                            background_color = pygame_menu.baseimage.BaseImage(
                                image_path="./Resources/Images/logo.png",
                                drawing_mode=pygame_menu.baseimage.IMAGE_MODE_SIMPLE,
                                drawing_offset=(220,20)
                            ),
                            title_bar_style=pygame_menu.widgets.MENUBAR_STYLE_NONE,
                            widget_font=pygame_menu.font.FONT_OPEN_SANS_BOLD,
                            widget_font_color=(0,0,0)

        )

        self.heading_font = pygame.font.Font('freesansbold.ttf', 24)


        self.window_size = [2 * board_size * cell_size + 3*margin, board_size * cell_size + 2*margin + 250]
        self.screen = pygame.display.set_mode(self.window_size)
        print(self.window_size)
        pygame.display.set_caption("Battleships")
        self.screen.fill(pygame.Color(236,240,241))

        self.inline_menu_surface = pygame.Surface((self.window_size[0] - 2*self.margin, 200 - self.margin))



    def start(self):
        main_menu = self.main_menu()
        main_menu.mainloop(self.screen, fps_limit=30)
            
    def main_menu(self):
        menu = pygame_menu.Menu(self.window_size[1], self.window_size[0], 
                                    "", theme=self.menu_theme)
        menu.add_button('Play', self.play)
        menu.add_button('Quit', pygame_menu.events.EXIT)
        return menu



    def play(self):
        self.aiTurn = aiTurn(self.board_size)
        self.screen.fill(pygame.Color((91, 196, 209)))
        
        pboard_heading = self.heading_font.render("Player board", True, pygame.Color("black"))
        pboard_heading_rect = pboard_heading.get_rect()
        pboard_heading_rect.center = (self.subwindow_positions["Player Board"][0]+ self.board_size/2 * self.cell_size, 40)
        self.screen.blit(pboard_heading, pboard_heading_rect)

        self.pboard = PlayerBoard(self.board_size, self.ship_types_list, 
                                    self.cell_size, self.border_size, 
                                    self.subwindow_positions["Player Board"])

        
        self.pboard.populate(self.screen, self.inline_menu_surface, self.subwindow_positions["Menu"])

        ai_heading = self.heading_font.render("Enemy board", True, pygame.Color("black"))
        ai_heading_rect = ai_heading.get_rect()
        ai_heading_rect.center = (self.subwindow_positions["AI Board"][0]+ self.board_size/2 * self.cell_size, 40)
        
        self.aiboard = AIBoard(self.board_size, self.ship_types_list, 
                                    self.cell_size, self.border_size, 
                                    self.subwindow_positions["AI Board"])
        
        while not self.game_over:
            if self.player_turn():
                self.ai_turn()
            self.screen.fill(pygame.Color((91, 196, 209)))
            self.screen.blit(ai_heading, ai_heading_rect)
            self.screen.blit(pboard_heading, pboard_heading_rect)
            self.aiboard.draw(self.screen)
            self.pboard.draw(self.screen)
            
            pygame.display.flip()
            pygame.time.Clock().tick(60)
            
    def player_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y, _ = self.aiboard.get_coordinates()
        if self.aiboard.valid_target(x, y):
            result = self.aiboard.shoot(x, y)
            if result == 2:
                Explosion(pygame.Rect(self.subwindow_positions["AI Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["AI Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
            elif result == 1:
                Ripple(pygame.Rect(self.subwindow_positions["AI Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["AI Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
            return True
        else:
            return False

    def ai_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y = -1, -1
        
        x,y = self.aiTurn.getLoc(self.pboard)
        
        if self.pboard.valid_target(x, y):
            result = self.pboard.shoot(x, y)

            if result == 2:
                Explosion(pygame.Rect(self.subwindow_positions["Player Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["Player Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
                if self.aiTurn.ai_hit_count == 0 or self.aiTurn.ai_hit_count == 1:
                            self.aiTurn.ai_hit_count+=1
                            self.aiTurn.attack_mode = 'd'                   

            elif result == 1:
                Ripple(pygame.Rect(self.subwindow_positions["Player Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["Player Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
                if self.aiTurn.ai_hit_count == 2 and self.aiTurn.ai_miss_after_hit_count < 2:
                    self.aiTurn.ai_miss_after_hit_count+=1                      
            return True
        else:
            return False

    @property
    def game_over(self):
        """Determines and prints the winner"""
        if self.aiboard.gameover:
            self.previous_win = True
            self.replay = True
            return True
        elif self.pboard.gameover:
            self.previous_win = False
            self.replay = True
            return True
        else:
            return False

    

if __name__ == "__main__":
    Game().start()
