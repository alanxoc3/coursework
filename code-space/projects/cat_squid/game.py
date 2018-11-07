#!/usr/bin/env python2.7

import pygame
import time

width, height = 640, 320

bkgd = pygame.image.load("trippy.png")
cat = pygame.image.load("cat.png")
squid = pygame.image.load("squid.png")
squidRects = []
surface = pygame.display.set_mode((width, height), pygame.HWSURFACE)
coordCat = [20, 20]
velocityCat = [0,0]
rectCat = cat.get_rect()
level = 0
isLevelFinished = True
pygame.init() # Set up stuf
pygame.display.set_caption("Hello Code_Space!") # Change the title.


def spawnSquids():
    for i in range(1, level + 4):
        curSquid = pygame.Rect(squid.get_rect())
        squidRects.append(curSquid)
        curSquid.x, curSquid.y = 0, height / i

running = True
while running:
    if isLevelFinished:
        level += 1
        spawnSquids()
        isLevelFinished = False
    coordCat[0] += velocityCat[0]
    coordCat[1] += velocityCat[1]

    surface.blit(bkgd, (0,0)) # Draws to the screen.
    surface.blit(cat, coordCat)
    for curSquid in squidRects:
        surface.blit(squid, (curSquid.x, curSquid.y))
    pygame.display.flip() # Updates the screen

    # And we want to quit if the X is pressed.
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                velocityCat = [-1,0]
            elif event.key == pygame.K_RIGHT:
                velocityCat = [1, 0]
            elif event.key == pygame.K_DOWN:
                velocityCat = [0, 1]
            elif event.key == pygame.K_UP:
                velocityCat = [0, -1]
            elif event.key == pygame.K_SPACE:
                coordCat = [0, 0]
        else:
            velocityCat = [0, 0]

    rectCat.x, rectCat.y = coordCat[0], coordCat[1]

    for curSquid in squidRects:
        if rectCat.colliderect(curSquid):
            coordCat = [0,0]



pygame.quit()
