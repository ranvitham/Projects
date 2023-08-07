"""
This card game uses object-oriented programming to create two different classes, a 'Card' and a 'Deck' class.
The 'Card' class:
   - assigns a card object a rank and a suit
   - print out the card information (repr function)
   - compare two card objects to find which one is better. 
The 'Deck' class uses card objects from the Card class to create the deck of cards. 
The 'Deck' class: 
   - initializes a deck object that takes in one constructor which indicates whether the deck object 
     should be initialized in sorted order or shuffled which is an optional parameter sorted by default 
   - initializes with a whole typical set of 52 cards for a deck object
   - allows the deck object to be shuffled, dealt, and reset
   - prints the number of cards that have been dealt, whether the deck has been shuffled, and that it 
     is a deck object (repr function)
"""
import numpy as np
import random

class Card:
    #A Card object maintains a `rank` and a `suit`

    _rank_to_str = {11: 'Jack', 12: 'Queen', 13: 'King', 14: 'Ace'}
    _suit_to_str = {'C': 'Clubs', 'H': 'Hearts', 'S': 'Spades', 'D': 'Diamonds'}

    def __init__(self, rank: int, suit: str):
        #Initializes Card object.
        assert 2 <= rank <= 14, #Valid ranks are [2, 14] for the ranks: [2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A]
        assert suit.upper() in {'C', 'H', 'S', 'D'}, #Valid suits are [C, H, S, D]

        self.rank = rank
        self.suit = suit

    def __repr__(self):
        #Returns the string representation of a card.
        _suit_to_str = {'C': 'Clubs', 'H': 'Hearts', 'S': 'Spades', 'D': 'Diamonds'}
        _rank_to_str = {11: 'Jack', 12: 'Queen', 13: 'King', 14: 'Ace'}
        
        if self.rank >= 11:
            ranks =  _rank_to_str[self.rank]
        if self.rank < 11:
            ranks = str(self.rank)
        
        yay = ranks + " of " +str(_suit_to_str[self.suit])
        return yay

    def __lt__(self, other):
        #Determines whether the rank of this card is less than the rank of the other.
        if self.rank < other.rank:
            return True
        else:
            return False
        pass

    def __gt__(self, other):
        #Determines whether the rank of this card is greater than the rank of the other.
        if self.rank > other.rank:
            return True
        else:
            return False
        pass

    def __le__(self, other):
        #Determines whether the rank of this card is less than or equal to the rank of the other.
        if self.rank <= other.rank:
            return True
        else:
            return False
        pass

    def __ge__(self, other):
        #Determines whether the rank of this card is greater than or equal to the rank of the other.
        if self.rank >= other.rank:
            return True
        else:
            return False
        pass

    def __eq__(self, other):
        #Determines whether the rank of this card is equal to the rank of the other.
        if self.rank == other.rank:
            return True
        else:
            return False
        pass



class Deck:
    shuffled = False 
    dealt=0
    deck=[]
    suits = ['C', 'H', 'S', 'D']
    ranks = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
    
    def __init__(self, shuffled=False):
        #Initializes the Deck object.
        self.shuffled = self.shuffled
        
        for x in self.suits:
            for y in self.ranks:
                self.deck.append(Card(y, x))
                if shuffled == True:
                    self.shuffle()
                    
            self.cards = self.deck

            
    def shuffle(self):
        #Shuffles the deck.
        self.shuffled = True
        random.shuffle(self.deck)
        
    def deal_card(self):
        #Deals the deck.
        if self.dealt < 52:
            self.dealt += 1
            
        else:
            return None
        return self.cards.pop(0)
    
        
    def __repr__(self):
        #Returns the string representation of a deck.
        return "Deck("+"dealt "+ str(self.dealt) + ", " +"shuffled=" + str(self.shuffled)+")"
        
        
    def reset(self):
        #Resets the new Deck so there is no need to create new Deck object.
        self.deck.clear()
        self.dealt = 0
        self.shuffled = self.shuffled
        
        for x in self.suits:
            for y in self.ranks:
                self.deck.append(Card(y, x))
            self.cards = self.deck
            
