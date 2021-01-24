import random

class AI():

    def __init__(self,size):
        self.switchToRandom()
        self.board_size = size
        self.ships_left = 5
        self.smallest_ship = 2
        self.sunk_list = [(-1,-1)]

    def switchToRandom(self):
        self.ai_hit_count = 0
        self.ai_miss_after_hit_count = 0
        self.ai_hit_direction = ''
        self.attack_mode = 'r'
        self.ai_init_hit = (-1,-1)


    def checkSpace(self, playerBoard, x, y):
        spaceNorth = True
        spaceEast = True
        spaceSouth = True
        spaceWest = True

        tempx, tempy = x,y
        
        for i in range(1,self.smallest_ship):
            if not playerBoard.valid_target(x,y+i):
                spaceSouth = False
                break

        for i in range(1,self.smallest_ship):
            if not playerBoard.valid_target(x,y-i):
                spaceNorth = False
                break
        for i in range(1,self.smallest_ship):
            if not playerBoard.valid_target(x+i,y):
                spaceEast = False
                break
        for i in range(1,self.smallest_ship):
            if not playerBoard.valid_target(x-i,y):
                spaceWest = False
                break

        if spaceEast or spaceNorth or spaceWest or spaceSouth:
            return False


        return True                
        

    def randomAttack(self,playerBoard):
        x,y = 5,5
        uselessLoc = False    
        while not playerBoard.valid_target(x, y) or uselessLoc:
            x = random.randint(0, self.board_size - 1)
            y = random.randint(0, self.board_size - 1)
            uselessLoc = self.checkSpace(playerBoard, x, y)
        return x,y

    def firstHit(self,playerBoard,x,y):
        
        x+=1
        if not playerBoard.valid_target(x,y):
            x-=1
            y+=1
        
        if not playerBoard.valid_target(x,y):
            x-=1
            y-=1
        
        if not playerBoard.valid_target(x,y):
            x+=1
            y-=1

        return x,y

    def secondHit(self,playerBoard):
        x,y = self.ai_init_hit
        x2,y2 = playerBoard.hits_list[-1]
        
        if x-x2 == 0:
            self.ai_hit_direction = 'v'
        elif y-y2 == 0:
            self.ai_hit_direction = 'h'

        if self.ai_hit_direction == 'v':

            if self.ai_miss_after_hit_count == 0:
            
                while (x,y) in playerBoard.hits_list:
                    y+=1
            
                if not playerBoard.valid_target(x,y):
                    self.ai_miss_after_hit_count += 1
                    y-=1  
            
            if self.ai_miss_after_hit_count == 1:
                while (x,y) in playerBoard.hits_list:
                    y-=1
            
                if not playerBoard.valid_target(x,y):
                    self.ai_miss_after_hit_count += 1
                    y+=1            
            
        if self.ai_hit_direction == 'h':
            
            if self.ai_miss_after_hit_count == 0:
            
                while (x,y) in playerBoard.hits_list:
                    x+=1
            
                if not playerBoard.valid_target(x,y):
                    self.ai_miss_after_hit_count += 1
                    x-=1    
            
            if self.ai_miss_after_hit_count == 1:
        
                while (x,y) in playerBoard.hits_list:
                    x-=1        
            
                if not playerBoard.valid_target(x,y):
                    self.ai_miss_after_hit_count += 1
                    x+=1

        return x,y                    

    def destroyerAttack(self,playerBoard):
        if self.ai_hit_count == 1:
            (x,y) = self.ai_init_hit
            if x == -1:
                x,y = playerBoard.hits_list[-1]
                self.ai_init_hit = (x,y)

            x,y = self.firstHit(playerBoard,x,y)

        if self.ai_hit_count == 2:
            x,y = self.secondHit(playerBoard)
        if self.ai_miss_after_hit_count == 2:

            allHitsDestroyed, x, y = self.checkAllHitsDestroyed(playerBoard)
            
            if allHitsDestroyed:
                self.switchToRandom()
                x,y = self.randomAttack(playerBoard)
           
            else:
                self.ai_init_hit = (x,y)
                self.ai_hit_count = 1
                self.ai_miss_after_hit_count = 0
                self.attack_mode = 'd'
                x,y = self.firstHit(playerBoard,x,y)            
                
        return x,y


    def setSmallestShipLength(self,playerBoard):
        self.smallest_ship = 5
        for ship in playerBoard.ships_list:
            if ship.length < self.smallest_ship and ship.active:
                self.smallest_ship = ship.length

    def getNumberOfActiveShips(self,playerBoard):

        activeShips = 0
        for ship in playerBoard.ships_list:
            if ship.active:
                activeShips+=1

        return activeShips        

    def updateSunkList(self, playerBoard):
        
        for ship in playerBoard.ships_list:
            if not ship.active:
                if ship.coordinate_list[0] not in self.sunk_list:
                    self.sunk_list += ship.coordinate_list


    def checkAllHitsDestroyed(self,playerBoard):

        for (x,y) in playerBoard.hits_list:
            if (x,y) not in self.sunk_list:
                return False ,x,y
        return True,-1,-1          

    def UpdateAttackMode(self,playerBoard):

        active_ships = self.getNumberOfActiveShips(playerBoard)

        if active_ships < self.ships_left:
            
            self.ships_left = active_ships
            self.setSmallestShipLength(playerBoard)
            self.updateSunkList(playerBoard)

            allHitsDestroyed, x, y = self.checkAllHitsDestroyed(playerBoard)
            
            if not allHitsDestroyed:
                self.ai_init_hit = (x,y)
                self.ai_hit_count = 1
                self.ai_miss_after_hit_count = 0
                self.attack_mode = 'd'
                x,y = self.firstHit(playerBoard,x,y)
                return False, x, y

            self.attack_mode = 'r'
            self.switchToRandom()    

        return True, -1, -1


    def getLoc(self,playerBoard):
       
        
        takeTurn,x,y = self.UpdateAttackMode(playerBoard)

        if takeTurn:
            if self.attack_mode == 'd':
                x,y = self.destroyerAttack(playerBoard)
            else:
                x,y = self.randomAttack(playerBoard)

        
        return x,y



    
