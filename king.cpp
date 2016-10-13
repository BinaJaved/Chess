#include "stdafx.h"
#include "king.h"


king::king( int col , int x , int y , int pindex , chesss * c)
{
	
	this ->index = pindex;
	this ->x = x;
	this ->y = y;
	this ->Cptr = c;
	if( col == 1 )
	{
		this ->imgPath = L"res\\white_king.png";
	}
	else
	{
		this ->imgPath = L"res\\black_king.png";
	}
	this ->color = col;
	castling = 1;
}




bool king:: move(int nx, int ny)
{
	bool a = this ->isValidCell(nx,ny);
	if(a == true )
	{
		this->Cptr->nullenpassent(this->color);
		if(Cptr->getCell(nx,ny)->Pc == NULL)
		{
			if( ny == y-2 )
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a = x;
				int b = y;
				this -> x = nx;
				this -> y = ny;
				Cptr->getCell(nx,3)->Pc = Cptr->getCell(nx,0)->Pc;
				rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,3)->Pc);
				ptr ->docastling( nx , 3 );
				Cptr->getCell(nx,0)->Pc = NULL;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					Cptr->getCell(nx,0)->Pc = Cptr->getCell(nx,3)->Pc;
					rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,0)->Pc);
					ptr ->docastling( nx , 0 );
					Cptr->getCell(nx,3)->Pc = NULL;
					return 0;
				}

				this ->castling = 0;
				return 1;
			}
			else if(ny == y+2)
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a = x;
				int b = y;
				this -> x = nx;
				this -> y = ny;
				Cptr->getCell(nx,5)->Pc = Cptr->getCell(nx,7)->Pc;
				rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,5)->Pc);
				ptr ->docastling( nx , 5 );
				Cptr->getCell(nx,7)->Pc = NULL;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					Cptr->getCell(nx,7)->Pc = Cptr->getCell(nx,5)->Pc;
					rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,7)->Pc);
					ptr ->docastling( nx , 0 );
					Cptr->getCell(nx,5)->Pc = NULL;
					return 0;
				}

				this ->castling = 0;
				return 1;
			}
			else
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a=x;
				int b=y;
				x = nx;
				y = ny;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					return 0;
				}
				this ->castling = 0;
				return 1;
			}
		}
		else if( Cptr->getCell(nx,ny)->Pc != NULL )
		{
			Piece * p = Cptr->getCell(nx,ny)->Pc;
			Cptr->getCell(nx,ny)->Pc = this;
			Cptr->getCell(x,y)->Pc = NULL;
			int a=x;
			int b=y;
			x = nx;
			y = ny;

			if( Cptr->isKingInCheck(this ->color) )
			{
				x=a;
				y=b;
				Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
				Cptr->getCell(nx,ny)->Pc = p;
				return 0;
			}
			Cptr->deletepiece( p->getindex() , p->gtcol() );
			this ->castling = 0;
			return 1;
		}
		return 0;
	}
	return 0;
}



bool king:: isValidCell(int nx, int ny)
{
	if( Piece :: isValidCell(nx, ny) )
	{
		if( ( nx == x-1 && ny == y-1 ) || ( nx == x-1 && ny == y+1 ) || ( nx == x-1 && ny == y ) || ( nx == x+1 && ny == y-1 ) ||  ( nx == x+1 && ny == y+1) || (nx == x+1 && ny == y ) ||  ( nx == x && ny == y-1 ) || ( nx == x && ny == y+1 ) )
		{
			if( Cptr->getCell(nx,ny)->Pc == NULL )
			{
				return 1;
			}
			else
			{
				if( Cptr->getCell(nx,ny)->Pc->gtcol() != this ->color )
				{
					return 1;
				}
				return 0;
			}
			return 0;
		}

		// castling 

		else if( ny == y-2 || ny == y+2 )
		{
			if( this ->castling == 1 )
			{
				if( ny == y-2 && nx == x)
				{
					bool a = true ;
					int i;
					for ( i=1 ; i<4 ; i++ )
					{
						if( Cptr->getCell(nx,y-i)->Pc != NULL )
						{
							a = false;
						}
					}
					if( a==true )
					{
						rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,y-i)->Pc);
						if( ptr != NULL )
						{
							if( ptr -> rook :: getcastling() == 1 )
							{
								return 1;
							}
							return 0;
						}
						return 0;
					}
					return 0;
				}
				else if( ny == y+2 && nx == x )
				{
					bool a = true ;
					int i;
					for ( i=1 ; i<3 ; i++ )
					{
						if( Cptr->getCell(nx,y+i)->Pc != NULL )
						{
							a = false;
						}
					}
					if( a==true )
					{
						rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,y+i)->Pc);
						if( ptr != NULL )
						{
							if( ptr -> rook :: getcastling() == 1 )
							{
								return 1;
							}
							return 0;
						}
						return 0;
					}
					return 0;
				}
				return 0;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}



bool king :: isOpponentChecked()
{
	if( Piece :: isValidCell(x-1, y-1) )
	{
		if( Cptr->getCell(x-1 , y-1)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x-1,y-1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x-1, y) )
	{
		if( Cptr->getCell(x-1 , y)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x-1,y)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x-1, y+1) )
	{
		if( Cptr->getCell(x-1 , y+1)->Pc !=NULL )
		{	
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x-1,y+1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x, y+1) )
	{
		if( Cptr->getCell(x , y+1)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x,y+1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x+1, y+1) )
	{
		if( Cptr->getCell(x+1 , y+1)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x+1,y+1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x+1, y) )
	{
		if( Cptr->getCell(x+1 , y)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x+1,y)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x+1, y-1) )
	{
		if( Cptr->getCell(x+1 , y-1)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x+1,y-1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	if( Piece :: isValidCell(x, y-1) )
	{
		if( Cptr->getCell(x , y-1)->Pc !=NULL )
		{
			king * ptr = dynamic_cast <king*>(Cptr->getCell(x,y-1)->Pc);
			if( ptr != NULL && ptr ->gtcol() != this ->color)
			{
				return 1;
			}
		}
	}
	return 0;
}




wchar_t* king:: getpath()
{
	return imgPath;
}

int king :: getx ()
{
	return x;
}


int king :: gety ()
{
	return y;
}


int king :: gtcol()
{
	return this ->color;
}


int king :: getindex()
{
	return this ->index;
}




bool king :: checkmatemove(int nx, int ny)
{
	bool a = this ->isValidCell(nx,ny);
	if(a == true )
	{
		this->Cptr->nullenpassent(this->color);
		if(Cptr->getCell(nx,ny)->Pc == NULL)
		{
			if( ny == y-2 )
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a = x;
				int b = y;
				this -> x = nx;
				this -> y = ny;
				Cptr->getCell(nx,3)->Pc = Cptr->getCell(nx,0)->Pc;
				rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,3)->Pc);
				ptr ->docastling( nx , 3 );
				Cptr->getCell(nx,0)->Pc = NULL;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					Cptr->getCell(nx,0)->Pc = Cptr->getCell(nx,3)->Pc;
					rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,0)->Pc);
					ptr ->docastling( nx , 0 );
					Cptr->getCell(nx,3)->Pc = NULL;
					return 1;
				}
				x=a;
				y=b;
				Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
				Cptr->getCell(nx,ny)->Pc = NULL;
				Cptr->getCell(nx,0)->Pc = Cptr->getCell(nx,3)->Pc;
				rook * ptr2 =dynamic_cast <rook*>(Cptr->getCell(nx,0)->Pc);
				ptr2 ->docastling( nx , 0 );
				Cptr->getCell(nx,3)->Pc = NULL;
				return 0;
				
			}
			else if(ny == y+2)
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a = x;
				int b = y;
				this -> x = nx;
				this -> y = ny;
				Cptr->getCell(nx,5)->Pc = Cptr->getCell(nx,7)->Pc;
				rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,5)->Pc);
				ptr ->docastling( nx , 5 );
				Cptr->getCell(nx,7)->Pc = NULL;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					Cptr->getCell(nx,7)->Pc = Cptr->getCell(nx,5)->Pc;
					rook * ptr =dynamic_cast <rook*>(Cptr->getCell(nx,7)->Pc);
					ptr ->docastling( nx , 0 );
					Cptr->getCell(nx,5)->Pc = NULL;
					return 1;
				}

				x=a;
				y=b;
				Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
				Cptr->getCell(nx,ny)->Pc = NULL;
				Cptr->getCell(nx,7)->Pc = Cptr->getCell(nx,5)->Pc;
				rook * ptr1 =dynamic_cast <rook*>(Cptr->getCell(nx,7)->Pc);
				ptr1 ->docastling( nx , 0 );
				Cptr->getCell(nx,5)->Pc = NULL;
				return 0;
			}
			else
			{
				Cptr->getCell(nx,ny)->Pc = this;
				Cptr->getCell(x,y)->Pc = NULL;
				int a=x;
				int b=y;
				x = nx;
				y = ny;

				if( Cptr->isKingInCheck(this ->color) )
				{
					x=a;
					y=b;
					Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
					Cptr->getCell(nx,ny)->Pc = NULL;
					return 1;
				}
				x=a;
				y=b;
				Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
				Cptr->getCell(nx,ny)->Pc = NULL;
				return 0;
			}
		}
		else if( Cptr->getCell(nx,ny)->Pc != NULL )
		{
			Piece * p = Cptr->getCell(nx,ny)->Pc;
			Cptr->getCell(nx,ny)->Pc = this;
			Cptr->getCell(x,y)->Pc = NULL;
			int a=x;
			int b=y;
			x = nx;
			y = ny;

			if( Cptr->isKingInCheck(this ->color) )
			{
				x=a;
				y=b;
				Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
				Cptr->getCell(nx,ny)->Pc = p;
				return 1;
			}
			x=a;
			y=b;
			Cptr->getCell(x,y)->Pc = Cptr->getCell(nx,ny)->Pc;
			Cptr->getCell(nx,ny)->Pc = p;
			return 0;
		}
		return 0;
	}
	return 1;
}



