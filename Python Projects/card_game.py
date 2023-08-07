"""

"""

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
        #Returns the string representation of this card.
        
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
