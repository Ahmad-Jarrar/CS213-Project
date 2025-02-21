import pygame

pygame.mixer.init()
class Animation():
    """Animation base class to run 2 types of animations (per frame and continous)"""
    def __init__(self, frames, rectange, speed, sound = None):
        self.frames = frames
        self.current_frame = 0
        self.rect = rectange
        self.speed = speed
        self.sound = sound
        self.ticks = 0
        for i in self.frames.keys():
            self.frames[i] = pygame.transform.scale(self.frames[i], self.rect.size)

    def play(self,screen):
        """Play entire animation sequence once"""
        if self.sound != None:
            self.sound.play()
        for i in range(len(self.frames.keys())):
            screen.blit(self.frames[i], self.rect)
            pygame.display.update()
            pygame.time.Clock().tick(self.speed)

    def show_current_frame(self, screen):
        """Display current frame (internal use in slow animation)"""
        screen.blit(self.frames[self.current_frame], self.rect)

    def show_next_frame(self, screen):
        """Display next frame (internal use in slow animation)"""
        screen.blit(self.frames[self.current_frame], self.rect)
        self.current_frame = (self.current_frame + 1) % len(self.frames.keys())
    
    def play_frame(self, screen):
        """Display one frame in slow animation"""
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
    sound = pygame.mixer.Sound("./Resources/Sounds/explosion.wav")
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 30, self.sound)


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
        4: pygame.image.load("./Resources/Images/ripple/5.png"),
        5: pygame.image.load("./Resources/Images/ripple/6.png"),
        6: pygame.image.load("./Resources/Images/ripple/7.png"),
        7: pygame.image.load("./Resources/Images/ripple/8.png"),
        8: pygame.image.load("./Resources/Images/ripple/9.png"),
        9: pygame.image.load("./Resources/Images/ripple/10.png"),
        10: pygame.image.load("./Resources/Images/ripple/11.png")
    }
    sound = pygame.mixer.Sound("./Resources/Sounds/splash.wav")
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 30, self.sound)

class Background(Animation):
    frames = {
        0: pygame.image.load("./Resources/Images/water/1.png"),
        1: pygame.image.load("./Resources/Images/water/2.png"),
        2: pygame.image.load("./Resources/Images/water/3.png"),
        3: pygame.image.load("./Resources/Images/water/4.png"),
        4: pygame.image.load("./Resources/Images/water/5.png"),
        5: pygame.image.load("./Resources/Images/water/6.png"),
        6: pygame.image.load("./Resources/Images/water/7.png"),
        7: pygame.image.load("./Resources/Images/water/8.png"),
        8: pygame.image.load("./Resources/Images/water/9.png"),
        9: pygame.image.load("./Resources/Images/water/10.png"),
        10: pygame.image.load("./Resources/Images/water/11.png"),
        11: pygame.image.load("./Resources/Images/water/12.png")
    }
    def __init__(self, rectange):
        super().__init__(self.frames, rectange, 4)