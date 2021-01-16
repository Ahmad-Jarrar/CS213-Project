import random

class aiTurn():

    def __init__(self,size):
        self.ai_hit_count = 0
        self.ai_miss_after_hit_count = 0
        self.ai_hit_direction = ''
        self.attack_mode = 'r'
        self.board_size = size

    def switchToRandom(self):
        self.ai_hit_count = 0
        self.ai_miss_after_hit_count = 0
        self.ai_hit_direction = ''
        self.attack_mode = 'r'
        self.ai_init_hit = (,)    

    def randomAttack(self,playerBoard):
        x,y = -1,-1    
        while not playerBoard.valid_target(x, y):
            x = random.randint(0, self.board_size - 1)
            y = random.randint(0, self.board_size - 1)
        return x,y

    def changeInitHit(self,x,y):
        self.ai_init_hit = (x,y)
        self.ai_hit_count = 2

    def firstHit(self,playerBoard):
        x,y = playerBoard.hits_list[-1]
        self.ai_init_hit = (x,y)
        x+=1
        if not playerBoard.valid_target(x,y):

            if (x,y) in  playerBoard.hits_list:
                self.changeInitHit(x,y)
                return -1,-1
            x-=1
            y+=1
        
        if not playerBoard.valid_target(x,y):
            if (x,y) in  playerBoard.hits_list:
                self.changeInitHit(x,y)
                return -1,-1
            x-=1
            y-=1
        
        if not playerBoard.valid_target(x,y):
            if (x,y) in  playerBoard.hits_list:
                self.changeInitHit(x,y)
                return -1,-1
            x+=1
            y-=1

        return x,y    

    def getLocAfterHit(self,playerBoard):

        if self.ai_hit_count == 1:
            x,y = self.firstHit(playerBoard)

        if self.ai_hit_count == 2:
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

        if self.ai_miss_after_hit_count == 2:
            self.switchToRandom()
            x,y = self.randomAttack(playerBoard)              
            
        return x,y

    
    def getLoc(self,playerBoard):
        
        if self.attack_mode == 'd':
            x,y = self.getLocAfterHit(playerBoard)
        else:
            x,y = self.randomAttack(playerBoard)

        return x,y            
    
