#Liaison série
import serial

#Tableaux et graphes
import matplotlib.pyplot as plt
import numpy as np

#Exportation Excel
import xlsxwriter

#Utilitaires
import time
from math import *



def fonctionnement(T,f):

    nbVal=T*f

    # On ouvre la communication
    ser = serial.Serial("COM3", baudrate=2000000, timeout=1)
    while(ser.is_open==False):
        print("Port en cours d'ouverture")


    # On attend que l'arduino soit prêt (si il n'est pas pret après 10sec, on arrete)
    t0=time.time()
    print("En attente de l'Arduino")
    while ser.in_waiting==0 and time.time()-t0<10:
        time.sleep(0.1)

    if ser.in_waiting==0:
        return("Echec de l'établissement de la communication")

    else:
        line=ser.readline()
         #On vide le port d'entrée
        print("Communication établie")

    ser.flush()

    # On recoie tant qu'on a pas 10 mesurer et tant que le temps d'attente est en dessous de 10 sec (pour pas bloquer)
    print("Démarrage des mesures")
    ti=time.time()
    to=time.time()
    n=0
    M=np.array([])

    while time.time()-ti<10 and n<nbVal:
        while ser.in_waiting>0 and n<nbVal:
            a=ser.readline()
            b=a.decode('ascii')
            c=str(b)
            d=int(c)
            M=np.append(M,[d])
            n+=1
            t0=time.time()

    print("Mesures terminées")
    print(time.time()-ti)

    print(M)
    plt.plot(M)
    plt.show()

