import pygame
import pygame_menu
from Board import PlayerBoard, AIBoard
from animations import Explosion, Ripple
from AI.AI import AI

class Game():
    """Main game class"""

    def __init__(self, board_size=8, cell_size=50, margin=20, border_size=0.3, 
                    ship_types=["Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"]):
        pygame.init()
        pygame.mixer.init()
        self.previous_win = False
        self.replay = False
        self.board_size = board_size
        self.cell_size = cell_size
        self.margin = margin
        self.border_size = border_size
        self.ship_types_list = ship_types
        # Calculate window size
        self.subwindow_positions = {
            "AI Board": [self.margin, self.margin + 50],
            "Player Board": [2*self.margin + board_size*cell_size, self.margin + 50],
        }
        # Set headings style
        self.heading_font = pygame.font.Font('./Resources/Fonts/Bebas-Regular.ttf', 24)
        self.text_color = pygame.Color(91, 196, 209)

        # Create game window
        self.window_size = [2 * board_size * cell_size + 3*margin, board_size * cell_size + 2*margin + 50]
        self.screen = pygame.display.set_mode(self.window_size)
        pygame.display.set_caption("Battleships")
        self.screen.fill(pygame.Color(173, 200, 216))
        # Start background 
        pygame.mixer.music.load("./Resources/Sounds/background.wav") 
        pygame.mixer.music.play(-1,0.0)

    def start(self):
        """Start game with main menu"""
        main_menu = self.main_menu()
        main_menu.mainloop(self.screen, fps_limit=30)
            
    def main_menu(self):
        """Build Main menu"""
        # Main menu style
        menu_theme = pygame_menu.themes.Theme(
                            surface_clear_color=(173, 200, 216),
                            background_color = pygame_menu.baseimage.BaseImage(
                                image_path="./Resources/Images/logo.png",
                                drawing_mode=pygame_menu.baseimage.IMAGE_MODE_SIMPLE,
                                drawing_offset=(295,10)
                            ),
                            title_bar_style=pygame_menu.widgets.MENUBAR_STYLE_NONE,
                            widget_font=pygame_menu.font.FONT_BEBAS,
                            widget_font_color=(0,0,0)
                            
        )
        menu = pygame_menu.Menu(self.window_size[1], self.window_size[0], 
                                    "", theme=menu_theme)
        menu.add_button('Play', self.play)

        # Help menu style
        help_theme = pygame_menu.themes.Theme(
            background_color=(173, 200, 216),
            title_bar_style=pygame_menu.widgets.MENUBAR_STYLE_NONE,
            widget_font=pygame_menu.font.FONT_FRANCHISE,
            widget_font_color=(0, 0, 0),
            widget_font_size=32,
        )

        help_menu = pygame_menu.Menu(
            self.window_size[1], self.window_size[0],
            theme=help_theme,
            title=''
        )
        HELP = [
            "Left Click to add/remove ships",
            "Right Click to rotate ships",
            "Press R to randomly place ships",
            "Press Escape to return to Main Menu"
        ]
        for m in HELP:
            help_menu.add_label(m, align=pygame_menu.locals.ALIGN_CENTER)
        help_menu.add_vertical_margin(25)
        help_menu.add_button('Return to Menu', pygame_menu.events.BACK)

        menu.add_button('Help', help_menu)
        menu.add_button('Quit', pygame_menu.events.EXIT)

        return menu

    def play(self):
        """
        Main game function
        Contains board population and main game loop
        """
        self.ai = AI(self.board_size)
        self.screen.fill(pygame.Color(33, 119, 148))
        # Display player board heading
        pboard_heading = self.heading_font.render("Player board", True, self.text_color)
        pboard_heading_rect = pboard_heading.get_rect()
        pboard_heading_rect.center = (self.subwindow_positions["Player Board"][0]+ self.board_size/2 * self.cell_size, 40)
        self.screen.blit(pboard_heading, pboard_heading_rect)
        
        self.pboard = PlayerBoard(self.board_size, self.ship_types_list, 
                                    self.cell_size, self.border_size, 
                                    self.subwindow_positions["Player Board"])
        # Populate player board
        self.pboard.populate(self.screen, self.subwindow_positions["AI Board"])
        # Display AI board heading
        ai_heading = self.heading_font.render("Enemy board", True, self.text_color)
        ai_heading_rect = ai_heading.get_rect()
        ai_heading_rect.center = (self.subwindow_positions["AI Board"][0]+ self.board_size/2 * self.cell_size, 40)
        
        self.aiboard = AIBoard(self.board_size, self.ship_types_list, 
                                    self.cell_size, self.border_size, 
                                    self.subwindow_positions["AI Board"])
        # Turn sync
        is_player_turn = True
        is_ai_turn = False
        # Delay to allow sound effect to play properly 
        delay_counter = 11

        while True:
            
            try:
                # Take turn
                if is_player_turn and delay_counter > 15:
                    is_player_turn = not self.player_turn()
                    is_ai_turn = not is_player_turn
                    delay_counter = 0
                
                elif is_ai_turn and delay_counter > 60:
                    is_ai_turn = not self.ai_turn()
                    is_player_turn = not is_ai_turn
                    delay_counter = 0
                else:
                    delay_counter += 1
            except Exception:
                # Exit exception
                break
            
            # Draw display components
            self.screen.fill(pygame.Color(33, 119, 148))
            self.screen.blit(ai_heading, ai_heading_rect)
            self.screen.blit(pboard_heading, pboard_heading_rect)
            self.aiboard.draw(self.screen)
            self.pboard.draw(self.screen)
            
            # Display frame
            pygame.display.flip()
            pygame.time.Clock().tick(60)

            # Display Game over screen and exit
            if self.game_over:
                # Overlay translucent screen
                score_surface = pygame.Surface(self.window_size)
                score_surface.set_alpha(200)
                score_surface.fill(pygame.Color(33, 119, 148))
                
                font = pygame.font.Font('./Resources/Fonts/Bebas-Regular.ttf', 60)
                # Add result
                if self.win:
                    score = font.render("You Win!", True, self.text_color)
                else:
                    score = font.render("You Lose!", True, self.text_color)

                score_rect = score.get_rect()
                score_rect.center = (self.window_size[0] //2, self.window_size[1] //2)
                score_surface.blit(score, score_rect)

                self.screen.blit(score_surface, (0,0))
                pygame.display.flip()
                pygame.time.Clock().tick(0.2)
                break
            
    def player_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y, button = self.aiboard.get_coordinates()

        if button == -2:
            raise Exception("exit")

        if self.aiboard.valid_target(x, y):
            result = self.aiboard.shoot(x, y)
            if result == 2:
                # Explosion on hit
                Explosion(pygame.Rect(self.subwindow_positions["AI Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["AI Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
            elif result == 1:
                # Splash on miss
                Ripple(pygame.Rect(self.subwindow_positions["AI Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["AI Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
            return True
        else:
            return False

    def ai_turn(self):
        """Uses input to decide if a shot is valid or not"""
        x, y = -1, -1
        x,y = self.ai.getLoc(self.pboard)
        
        if self.pboard.valid_target(x, y):
            result = self.pboard.shoot(x, y)

            if result == 2:
                Explosion(pygame.Rect(self.subwindow_positions["Player Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["Player Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
                if self.ai.ai_hit_count == 0 or self.ai.ai_hit_count == 1:
                            self.ai.ai_hit_count+=1
                            self.ai.attack_mode = 'd'                   

            elif result == 1:
                Ripple(pygame.Rect(self.subwindow_positions["Player Board"][0] + x * self.cell_size,
                                      self.subwindow_positions["Player Board"][1] + y * self.cell_size,
                                      self.cell_size, self.cell_size)).play(self.screen)
                if self.ai.ai_hit_count == 2 and self.ai.ai_miss_after_hit_count < 2:
                    self.ai.ai_miss_after_hit_count+=1                      
            return True
        else:
            return False

    @property
    def game_over(self):
        """Determines and prints the winner"""
        if self.aiboard.gameover:
            self.win = True
            return True
        elif self.pboard.gameover:
            self.win = False
            return True
        else:
            return False  

if __name__ == "__main__":
    Game().start()
