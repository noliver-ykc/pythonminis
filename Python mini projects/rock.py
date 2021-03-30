import random

def play():
    user = input("'r' for rock, 'p' for paper, 's' for scissors. Type now!\n")
    computer = random.choice(['r','p', 's'])
    #print(f"{computer}")
    
    if user == computer:
        return 'tie'
    
    if is_win(user, computer):
        return 'You won'
    
    return 'you lose'
    
def is_win(player, oppponent):
    if (player == 'r' and oppponent == 's') or (player == 's' and oppponent == 'p') or (player == 'p' and oppponent == 'r'):
            return True
            
print(play())

# python rock.py