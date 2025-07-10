import textwrap
import random
import time

All = {
"CategoryName": """
Anotação 1, XxXXX Ended1.

Anotação 2, YYYYYY Ended2.

""",

"FantasticCategoryName": """
Anotação 1, ZZZZZ Ended1.
""",

"WowCategoryName": """ 
Anotação 1, XYXYXYXY Ended1.
"""
}

def TotalAnots(type):
  X = 1
  while All[type].find(f"Anotação {X},") != -1:
    X+=1
    
  if All[type].find(f"Anotação {X},") == -1:
    return X - 1

def FindAnot(type):
  print("Escolha um numero de anotação")
  print("Total Anots: ", TotalAnots(type))
  Choice = input("Aqui: ")
  if Choice != None:
    Pos = All[type].find(f"Anotação {Choice},")
    End = All[type].find(f"Ended{Choice}.")
    Anot = All[type][Pos:End]
    if random.randint(1,1) == 1:
      print(textwrap.fill(Anot, width=50))
      print(" ")
    else:
      C =  45
      while Pos < End:
        print(Anot[Pos:Pos+C])
        Pos += C
  #apenas para desabilitar o segundo método. reabilitação ainda possivel
  
    print("Outra? 1.S, 2.N (Volta para o menu principal)")
    Choice = int(input("Aq"))
    if Choice == 1:
      FindAnot(type)
    elif Choice == 2:
      Main()

def Main():
  Categorys = list(All.keys())
  print("Escolha uma categoria")
  print(Categorys)
  Choice = input("Aqui: ")
  if Choice in Categorys:
    FindAnot(Choice)
  else:
    print("Inválido")
    time.sleep(2)
    Main()
  
Main()
