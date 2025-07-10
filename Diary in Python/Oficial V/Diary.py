import time

Categorys = {}

def invalidate(func, msg, temp):
  print("Opção invalida" if msg == None else msg)
  time.sleep(1 if temp == None else temp)
  func()

def Initialize():
  print("Serão quantas categorias de anotação?")
  Escolha = input()
  if Escolha.isnumeric():
    TotalCaty = int(Escolha)
    print(f"{TotalCaty} anotações. Fale o nome delas, no estilo \"X~ Y~ Z\" ")
    #Depois eu faço um método de separar melhor
    Names = input()
    if isinstance(Names, str):
      print("Digite a primeira anotação de cada uma, exemplo \"A~ B~ C\" ")
      First = input()
      Divide = Names.split("~")
      Divide2 = First.split("~")
      if len(Divide) == TotalCaty and len(Divide2) == TotalCaty:
        for i in range(TotalCaty):
          Categorys[Divide[i]] = [Divide2[i]]
        print(f"Categorias Criadas {Categorys}")
        time.sleep(1)
        midd()
      else:
        invalidate(Initialize, "As contas n batem", 2)
          
  else:
    invalidate(Initialize, "Digite um número!", 2)

def midd():
  print("Deseja ver o menu principal?")
  print("1. Sim")
  print("2. Não")
  Quer = input()
  if Quer.isnumeric():
    if int(Quer) == 1:
      Main()
    else:
      print("Chato")
  else:
    invalidate(midd, None, None)

def Main():
  print("O que deseja fazer?")
  print("1. Ver anotações")
  print("2. Adicionar uma anotação")
  print("3. Adicionar uma categoria")
  Ans = input()
  if Ans.isnumeric():
    Ans = int(Ans)
    if Ans == 1:
      print("Todas ou de uma categoria especifica?")
      print("1. Todas")
      print("2. Especifico")
      Ans2 = input()
      if Ans2.isnumeric():
        Ans2 = int(Ans2)
        if Ans2 == 1:
          print(Categorys)
          time.sleep(3)
          midd()
        elif Ans2 == 2:
          print(list(Categorys.keys()))
          print("Qual deseja?")
          Ans3 = input()
          if isinstance(Ans3, str):
            print(Categorys.get(Ans3, "Não encontrado"))
            time.sleep(3)
            midd()
          else:
            invalidate(Main, None, None)
      else:
        invalidate(Main, None, None)
    elif Ans == 2:
      print(list(Categorys.keys()))
      print("Para qual categoria?")
      Ans4 = input()
      if isinstance(Ans4, str):
        exists = Categorys.get(Ans4)
        if exists:
          print("Digite a anotação")
          Ans5 = input()
          if Ans5:
            Categorys[Ans4] = Ans5
            print("Anotação feita")
            time.sleep(1)
            print(Categorys[Ans4])
            time.sleep(3)
            midd()
          else:
            invalidate(Main, None, None)
        else:
          invalidate(Main, None, None)
      else:
        invalidate(Main, "Categoria Inválida", None)
    elif Ans == 3:
      print("Fale o nome da categoria")
      Ans6 = input()
      if isinstance(Ans6, str):
        print("Digite a primeira anotação dela")
        Ans7 = input()
        if Ans7:
          Categorys[Ans6] = Ans7
          print("Categoria criada")
          print(Categorys)
          time.sleep(3)
          midd()
        else:
          Invalidate(Main, "Resposta Vazia", None)
      else:
        invalidate(Main, "Categoria Inválida", None)
    else:
      invalidate(Main, None, None)
  else:
    invalidate(Main, None, None)

Initialize()

#Depois eu diminuo essas 20 gerações de familias if, fazendo mais dicionários e quebrando em mais funções