import pygame 
from pygame.locals import *

# initialization of pygame 
pygame.init()
# set up distlay window
width, height = 640, 480 
screen = pygame.display.set_mode((width, height))
keys = [False, False, False, False] # W-A-S-D
playerpos = [100, 100]
# load the image of bunny 
player = pygame.image.load("resources/images/dude.png")
grass = pygame.image.load("resources/images/grass.png")
castle = pygame.image.load("resources/images/castle.png")

while True: 
    # fill the screen with black
    screen.fill(0)
    for x in range(int(width / grass.get_width() + 1)):
        for y in range(int(height / grass.get_height() + 1)):
            screen.blit(grass, (x * 100, y * 100))
    screen.blit(castle, (0, 30))
    screen.blit(castle, (0, 135))
    screen.blit(castle, (0, 240))
    screen.blit(castle, (0, 345))
    # add bunny to screen at x = 100, y = 100
    screen.blit(player, playerpos)
    # update the screen 
    pygame.display.flip()
    # check for any new events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit(0)
        if event.type == pygame.KEYDOWN:
            if event.key==K_w:
                keys[0]=True
            elif event.key==K_a:
                keys[1]=True
            elif event.key==K_s:
                keys[2]=True
            elif event.key==K_d:
                keys[3]=True
        if event.type == pygame.KEYUP:
            if event.key==pygame.K_w:
                keys[0]=False
            elif event.key==pygame.K_a:
                keys[1]=False
            elif event.key==pygame.K_s:
                keys[2]=False
            elif event.key==pygame.K_d:
                keys[3]=False
        
    # 9 - Move player
    if keys[0]:
        playerpos[1]-=5
    elif keys[2]:
        playerpos[1]+=5
    if keys[1]:
        playerpos[0]-=5
    elif keys[3]:
        playerpos[0]+=5