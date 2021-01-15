import pygame

class Animation():
    def __init__(self, frames, rectange, speed):
        self.frames = frames
        self.current_frame = 0
        self.rect = rectange
        self.speed = speed
        self.ticks = 0
        for i in self.frames.keys():
            self.frames[i] = pygame.transform.scale(self.frames[i], self.rect.size)

    def play(self,screen):
        for i in range(len(self.frames.keys())):
            screen.blit(self.frames[i], self.rect)
            pygame.display.update()
            pygame.time.Clock().tick(self.speed)

    def show_current_frame(self, screen):
        screen.blit(self.frames[self.current_frame], self.rect)

    def show_next_frame(self, screen):
        screen.blit(self.frames[self.current_frame], self.rect)
        self.current_frame = (self.current_frame + 1) % len(self.frames.keys())
    
    def play_frame(self, screen):
        if self.ticks <= self.speed:
            self.show_current_frame(screen)
            self.ticks += 1
        else:
            self.ticks = 0
            self.show_next_frame(screen)


class Explosion(Animation):
    frames = {
        0: pygame.image.load("./Resources/Images/explosion/blowup1.png"),
        1: pygame.image.load("./Resources/Images/explosion/blowup2.png"),
        2: pygame.image.load("./Resources/Images/explosion/blowup3.png"),
        3: pygame.image.load("./Resources/Images/explosion/blowup4.png"),
        4: pygame.image.load("./Resources/Images/explosion/blowup5.png"),
        5: pygame.image.load("./Resources/Images/explosion/blowup6.png")
    }
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 30)


class Smoke(Animation):
    frames = {
        0: pygame.image.load("./Resources/Images/smoke/f0.png"),
        1: pygame.image.load("./Resources/Images/smoke/f1.png"),
        2: pygame.image.load("./Resources/Images/smoke/f2.png"),
        3: pygame.image.load("./Resources/Images/smoke/f3.png"),
        4: pygame.image.load("./Resources/Images/smoke/f4.png"),
        5: pygame.image.load("./Resources/Images/smoke/f5.png"),
        6: pygame.image.load("./Resources/Images/smoke/f6.png"),
        7: pygame.image.load("./Resources/Images/smoke/f7.png"),
        8: pygame.image.load("./Resources/Images/smoke/f8.png")
    }
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 2)

class Ripple(Animation):
    frames = {
        0: pygame.image.load("./Resources/Images/ripple/1.png"),
        1: pygame.image.load("./Resources/Images/ripple/2.png"),
        2: pygame.image.load("./Resources/Images/ripple/3.png"),
        3: pygame.image.load("./Resources/Images/ripple/4.png"),
        4: pygame.image.load("./Resources/Images/ripple/5.png")
    }
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 50)