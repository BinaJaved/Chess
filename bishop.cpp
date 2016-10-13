#include "stdafx.h"
#include "bishop.h"


bishop::bishop( int col , int x , int y , int pindex , chesss * c)
{
	
	this ->index = pindex;
	this ->x = x;
	this ->y = y;
	this ->Cptr = c;
	if( col == 1 )
	{
		this ->imgPath = L"res\\white_bishop.png";
	}
	else
	{
		this ->imgPath = L"res\\black_bishop.png";
	}
	this ->color = col;
}


bool bishop :: isValidCell(int nx, int ny)
{
	bool a = Piece :: isValidCell(nx,ny);
	if(a == true )
	{
		if( nx-x == ny-y || nx-x == -1* (ny-y) )
		{
			
			if( nx<x && ny<y )
			{
				int tempx = x-1;
				int tempy = y-1;
				bool b = true;
				while( tempx > nx && tempy > ny && b == true)
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						b = false;
					}
					tempx = tempx - 1;
					tempy = tempy - 1;
				}
				if( b == true )
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						if( Cptr->getCell(tempx,tempy)->Pc->gtcol() != this ->color )
						{
							return 1;
						}
						return 0;
					}
					return 1;
				}
				return 0;
			}
			else if( nx<x && ny>y )
			{
				int tempx = x-1;
				int tempy = y+1;
				bool b = true;
				while( tempx > nx  && b == true)
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						b = false;
					}
					tempx = tempx - 1;
					tempy = tempy + 1;
				}
				if( b == true )
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						if( Cptr->getCell(tempx,tempy)->Pc->gtcol() != this ->color )
						{
							return 1;
						}
						return 0;
					}
					return 1;
				}
				return 0;
			}
			else if ( nx>x && ny<y )
			{
				int tempx = x+1;
				int tempy = y-1;
				bool b = true;
				while( tempx < nx && b == true)
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						b = false;
					}
					tempx = tempx + 1;
					tempy = tempy - 1;
				}
				if( b == true )
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						if( Cptr->getCell(tempx,tempy)->Pc->gtcol() != this ->color )
						{
							return 1;
						}
						return 0;
					}
					return 1;
				}
				return 0;
			}
			else if( nx>x && ny>y )
			{
				int tempx = x+1;
				int tempy = y+1;
				bool b = true;
				while( tempx > nx && tempy > ny && b == true)
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						b = false;
					}
					tempx = tempx + 1;
					tempy = tempy + 1;
				}
				if( b == true )
				{
					if( Cptr->getCell(tempx,tempy)->Pc != NULL )
					{
						if( Cptr->getCell(tempx,tempy)->Pc->gtcol() != this ->color )
						{
							return 1;
						}
						return 0;
					}
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




bool bishop :: move(int nx, int ny)
{
	bool a = this ->isValidCell(nx,ny);
	if(a == true )
	{
		this->Cptr->nullenpassent(this->color);
		if(Cptr->getCell(nx,ny)->Pc == NULL)
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
			return 1;
		}
		else
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
			return 1;
		}
		return 0;
	}
	return 0;
}


bool bishop :: isOpponentChecked()
{ 
	
	int a = x-1;
	int b = y-1;
	while( a>=0 && b>=0 &&  Cptr->getCell(a,b)->Pc ==NULL )
	{
		a = a - 1;
		b = b - 1;
	}
	if(a>=0 && b>=0 && Cptr->getCell(a,b)->Pc !=NULL )
	{
		king * ptr = dynamic_cast <king*>(Cptr->getCell(a,b)->Pc);
		if( ptr != NULL && ptr ->gtcol() != this ->color)
		{
			return 1;
		}
	}

	a = x-1;
	b = y+1;
	while( a>=0 && b<=7 &&  Cptr->getCell(a,b)->Pc ==NULL )
	{
		a = a - 1;
		b = b + 1;
	}
	if(a>=0 && b<=7 && Cptr->getCell(a,b)->Pc !=NULL )
	{
		king * ptr = dynamic_cast <king*>(Cptr->getCell(a,b)->Pc);
		if( ptr != NULL && ptr ->gtcol() != this ->color)
		{
			return 1;
		}
	}


	a = x+1;
	b = y-1;
	while( a<=7 && b>=0 &&  Cptr->getCell(a,b)->Pc ==NULL )
	{
		a = a + 1;
		b = b - 1;
	}
	if(a<=7 && b>=0 &&  Cptr->getCell(a,b)->Pc !=NULL )
	{
		king * ptr = dynamic_cast <king*>(Cptr->getCell(a,b)->Pc);
		if( ptr != NULL && ptr ->gtcol() != this ->color)
		{
			return 1;
		}
	}

	a = x+1;
	b = y+1;
	while( a<=7 && b<=7 &&  Cptr->getCell(a,b)->Pc ==NULL )
	{
		a = a + 1;
		b = b + 1;
	}
	if(a<=7 && b<=7 && Cptr->getCell(a,b)->Pc !=NULL )
	{
		king * ptr = dynamic_cast <king*>(Cptr->getCell(a,b)->Pc);
		if( ptr != NULL && ptr ->gtcol() != this ->color)
		{
			return 1;
		}
	}
	return 0;	
}



wchar_t* bishop:: getpath()
{
	return imgPath;
}


int bishop:: getx ()
{
	return x;
}


int bishop:: gety ()
{
	return y;
}



bool bishop:: checkmatemove(int nx, int ny)
{
	bool a = this ->isValidCell(nx,ny);
	if(a == true )
	{
		this->Cptr->nullenpassent(this->color);
		if(Cptr->getCell(nx,ny)->Pc == NULL)
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
		else
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