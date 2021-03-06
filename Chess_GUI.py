"""
    This program uses the tkinter class to create the GUI applications and visuals for the chess game. 
    Utilizes the graphical representation to output the board, which is then displayed graphically through a TkInter window. 
    Each piece is represented with a two letter code, where the first letter represents the colour and the second represents 
    the piece type. When a move is made by the player the program will use the board representation to preform the move, 
    and then a fucntion will interperet the new layout of the board representation. The program then reconfigures the 
    board to display the new layout as deffined by the board representation. The board itself is created through 
    TkInter and is made up of different coloured squares.
    
"""

import tkinter as tk
root=tk.Tk()
dim_s = 64
tile_c = dim_s/2
board_rep=[
    ['br','bn ','bb', 'bq', 'bk', 'bb', 'bn', 'br'],
    ['bp', 'bp', 'bp', 'bp', 'bp ', 'bp', 'bp', 'bp'],
    [' ', ' ', ' ', ' ', '', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', '', ' ', ' ', ' '],
    ['wp', 'wp', 'wp', 'wp', 'wp ', 'wp', 'wp', 'wp'],
    ['wr', 'wn', 'wb', 'wq ', 'wk', 'wb', 'wn', 'wr']]



bb1=tk.PhotoImage(file="./Chess Pieces/bishopb.gif")
bk1=tk.PhotoImage(file="./Chess Pieces/kingb.gif")
bn1=tk.PhotoImage(file="./Chess Pieces/knightb.gif")
bp1=tk.PhotoImage(file="./Chess Pieces/pawnb.gif")
bq1=tk.PhotoImage(file="./Chess Pieces/queenb.gif")
br1=tk.PhotoImage(file="./Chess Pieces/rookb.gif")

wb1=tk.PhotoImage(file="./Chess Pieces/bishopw.gif")
wk1=tk.PhotoImage(file="./Chess Pieces/kingw.gif")
wn1=tk.PhotoImage(file="./Chess Pieces/knightw.gif")
wp1=tk.PhotoImage(file="./Chess Pieces/pawnw.gif")
wq1=tk.PhotoImage(file="./Chess Pieces/queenw.gif")
wr1=tk.PhotoImage(file="./Chess Pieces/rookw.gif")
empty=' '

class Board(tk.Frame):


    def interpretor(line):
        i,j=0,0
        for letter in line:
             if letter=="wr" or letter=="wn" or letter=="wb" or letter=="wq" or letter=="wk" or letter=="wp" or letter=="br" or letter=="bn" or letter=="bb" or letter=="bq" or letter=="bk" or letter=="bp":
                   board_rep[i][j]=letter


    def refresh():

        i,j=0,0
        for i in range(8):
           for j in range(8):
              if board_rep[i][j]=="wr" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wr1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="wn" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wn1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="wb" :
                tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wb1)
                tk.canvas.pack()
              elif board_rep[i][j]=="wq" :
                 tk. canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wq1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="wk" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wk1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="wp" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=wp1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="br" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=br1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="bn" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=bn1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="bb" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=bb1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="bq" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=bq1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="bk" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=bk1)
                 tk.canvas.pack()
              elif board_rep[i][j]=="bp" :
                 tk.canvas.create_image(tile_c+i*dim_s,tile_c+j*dim_s,image=bp1)
                 tk.canvas.pack()

    def __init__(self,parent, row=8,columns=8, size=32, WS='white',BS='black'):
        tk.Frame.__init__(self,parent)
        self.row = row
        self.columns = columns
        self.size = size
        self.WS = WS
        self.BS = BS
        self.pieces = {}

        canvas_width = columns * size
        canvas_height = row * size
        self.canvas = tk.Canvas(self, borderwidth=0, highlightthickness=0, width=canvas_width, height=canvas_height, background="grey")
        self.canvas.pack(side="top", fill="both", expand=True, padx=2, pady=2)
        self.canvas.bind("<Configure>", self.Draw)

    def exit(self):
        self.destroy()
        exit()

    def Draw(self, event):
        xsize = int((event.width-1) / self.columns)
        ysize = int((event.height-1) / self.row)
        self.size = min(xsize, ysize)
        self.canvas.delete("square")
        colour = self.BS
        for row in range(self.row):
            colour = self.WS if colour == self.BS else self.BS
            for col in range(self.columns):
                x1 = (col * self.size)
                y1 = (row * self.size)
                x2 = x1 + self.size
                y2 = y1 + self.size
                self.canvas.create_rectangle(x1, y1, x2, y2, outline="black", fill=colour, tags="square")
                colour = self.WS if colour == self.BS else self.BS

    def drag_piece(self, widget):
        widget.bind("<ButtonPress-1>",self.on_start)
        widget.bind("<B1-Motion>",self.on_drag)
        widget.bind("<ButtonRelease-1>", self.on_drop)
        widget.configure(corsor="hand1")

    def on_start(self,event):
        pass
    def on_drag(self,event):
        pass
    def on_drop(self,event):
        x,y = event.widget.winfo_pointerxy()
        target = event.widget.winfo_containting(x,y)
        try:
            target.configure(image=event.widget.cget("image"))
        except:
            pass


if __name__== '__main__':
    root = tk.Tk()
    board = Board(root)
    board.pack(side="top", fill="both", expand="true", padx=4, pady=4)
    root.mainloop()








