class aiTurn():

    def __init__(self):
        self.ai_hit_count = 0
        self.ai_miss_after_hit_count = 0
        self.ai_hit_direction = ''

    def getLocAfterHit(self,playerBoard):

        if self.ai_hit_count == 1:
            x,y = playerBoard.hits_list[-1]
            self.ai_init_hit = (x,y)
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
            self.ai_hit_count = 0
            self.ai_miss_after_hit_count = 0
            self.ai_hit_direction = ''
            x,y = self.ai_init_hit              
            
        return x,y
