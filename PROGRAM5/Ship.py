import pygame

pygame.mixer.init()
ship_destruction_sound = pygame.mixer.Sound("./Resources/Sounds/explosion.wav")

ship_images_active = {
    "Destroyer": pygame.image.load("./Resources/Images/ships/2.png"),
    "Submarine": pygame.image.load("./Resources/Images/ships/3s.png"),
    "Cruiser": pygame.image.load("./Resources/Images/ships/3c.png"),
    "Battleship": pygame.image.load("./Resources/Images/ships/5.png"),
    "Carrier": pygame.image.load("./Resources/Images/ships/4.png")
}

ship_images_destroyed = {
    "Destroyer": pygame.image.load("./Resources/Images/ships/2.png"),
    "Submarine": pygame.image.load("./Resources/Images/ships/3s.png"),
    "Cruiser": pygame.image.load("./Resources/Images/ships/3c.png"),
    "Battleship": pygame.image.load("./Resources/Images/ships/5.png"),
    "Carrier": pygame.image.load("./Resources/Images/ships/4.png")
}

ship_sizes = {
    "Destroyer": 2,
    "Submarine": 3,
    "Cruiser": 3,
    "Battleship": 5,
    "Carrier": 4
}
directions = {
    "NORTH": 0,
    "EAST": 1,
    "SOUTH": 2,
    "WEST": 3
}

class Ship:
    """An object to store the data of one ship"""
    

    

    def __init__(self, x, y, d, type, cell_size):
        self.location = (x, y)
        self.direction = d
        self.type = type
        self.length = ship_sizes[type]
        self.cell_size = cell_size
        self.active = True
        self.assign_image(ship_images_active[type])
        
    def assign_image(self, image):
        self.image = pygame.transform.scale(image, (self.cell_size, self.length * self.cell_size))
        self.image = pygame.transform.rotate(self.image, self.direction * 90)

    def destroy(self):

        ship_destruction_sound.play()
        self.active = False
        self.assign_image(ship_images_destroyed[self.type])

    @property
    def size(self):
        if self.direction % 2 == 0:
            return [self.length * self.cell_size, self.cell_size]
        else:
            return [self.cell_size, self.length * self.cell_size]

    @property
    def coordinate_list(self):
        """Calculates the list of coordinates that the ship is located over"""
        x, y = self.location
        if self.direction == directions["NORTH"]:
            return [(x, y - i) for i in range(self.length)]
        elif self.direction == directions["EAST"]:
            return [(x + i, y) for i in range(self.length)]
        elif self.direction == directions["SOUTH"]:
            return [(x, y + i) for i in range(self.length)]
        elif self.direction == directions["WEST"]:
            return [(x - i, y) for i in range(self.length)]

    @property
    def starting_position(self):
        if self.direction == directions["NORTH"]:
            return [self.location[0] * self.cell_size, (self.location[1] - self.length + 1) * self.cell_size]

        elif self.direction == directions["EAST"] or self.direction == directions["SOUTH"]:
            return [self.location[0] * self.cell_size, self.location[1] * self.cell_size]

        elif self.direction == directions["WEST"]:
            return [(self.location[0] - self.length + 1) * self.cell_size, self.location[1] * self.cell_size]

    def rotate(self):
        """Rotates the ship"""
        self.direction = (self.direction + 1) % 4
        self.image = pygame.transform.rotate(self.image, 90)

    def __repr__(self):
        """A nice representation of the Ship object, for debugging"""
        return "<Ship Object: ({},{}), {}, Length {}>".format(
            *self.location, self.direction, self.length)

    def draw(self, screen):
        pos = self.starting_position
        size = self.size
        screen.blit(self.image, pygame.Rect([pos[0], pos[1], size[0], size[1]]))