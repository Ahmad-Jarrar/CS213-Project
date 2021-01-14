import pygame

class Ship:
    """An object to store the data of one ship"""
    ship_type = {
        2: pygame.image.load("./Resources/Images/size2.png"),
        3: pygame.image.load("./Resources/Images/size3.png"),
        4: pygame.image.load("./Resources/Images/size4.png")
    }

    directions = {
        "NORTH": 0,
        "EAST": 1,
        "SOUTH": 2,
        "WEST": 3
    }

    def __init__(self, x, y, d, l, cell_size):
        self.location = (x, y)
        self.direction = d
        self.length = l
        self.cell_size = cell_size
        self.image = pygame.transform.scale(self.ship_type[l], (cell_size, l * cell_size))
        self.image = pygame.transform.rotate(self.image, d * 90)

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
        if self.direction == Ship.directions["NORTH"]:
            return [(x, y - i) for i in range(self.length)]
        elif self.direction == Ship.directions["EAST"]:
            return [(x + i, y) for i in range(self.length)]
        elif self.direction == Ship.directions["SOUTH"]:
            return [(x, y + i) for i in range(self.length)]
        elif self.direction == Ship.directions["WEST"]:
            return [(x - i, y) for i in range(self.length)]

    @property
    def starting_position(self):
        if self.direction == Ship.directions["NORTH"]:
            return [self.location[0] * self.cell_size, (self.location[1] - self.length + 1) * self.cell_size]

        elif self.direction == Ship.directions["EAST"] or self.direction == Ship.directions["SOUTH"]:
            return [self.location[0] * self.cell_size, self.location[1] * self.cell_size]

        elif self.direction == Ship.directions["WEST"]:
            return [(self.location[0] - self.length + 1) * self.cell_size, self.location[1] * self.cell_size]

    def rotate(self):
        """Rotates the ship"""
        self.direction = (self.direction + 1) % 4
        self.image = pygame.transform.rotate(self.image, 90)

    def __repr__(self):
        """A nice representation of the Ship object, for debugging"""
        return "<Ship Object: ({},{}), {}, Length {}>".format(
            *self.location, self.direction, self.length)

    def draw(self, screen, margin, offset):
        pos = self.starting_position
        size = self.size
        screen.blit(self.image, pygame.Rect([pos[0] + offset, pos[1] + margin, size[0], size[1]]))