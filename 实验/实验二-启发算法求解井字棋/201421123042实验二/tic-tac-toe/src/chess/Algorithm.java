package chess;

import java.util.Random;

public class Algorithm {
	public static   final   char  empty = ' ';
	public static   final   char  x = 'X';
	public static   final   char  o = 'O';
	public static   final   int   INFINITY = 100 ;   // ��ʾ�����ֵ   
	public static   final   int   WIN = +INFINITY ;   // MAX���������Ϊ������   
	public static   final   int   LOSE = -INFINITY ;   // MAX����С���棨��MIN�������棩Ϊ������   
	public static   final   int   DOUBLE_LINK = INFINITY / 2 ;   // ���ͬһ�С��л�Խ�������������������   
	public static   final   int   INPROGRESS = 1 ;   // �Կɼ����£�û��ʤ����;֣�   
	public static   final   int   DRAW = 0 ;   // �;�   
	public static   final   int [][] WIN_STATUS =   {   
	      {   0, 1, 2 },   
	      { 3, 4, 5 },   
	      { 6, 7, 8 },   
	      { 0, 3, 6 },   
	      { 1, 4, 7 },   
	      { 2, 5, 8 },   
	      { 0, 4, 8 },   
	      { 2, 4, 6   }   
	};   
	
	
	//����ʱ��ÿ��λ�õĹ�ֵ   
	static   final   int []   INITIAL_POS_VALUE   = {   
	      3, 2, 3,   
	      2, 4, 2,   
	      3, 2, 3  
	};   
	/**  
	 * ��ֵ�������ṩһ������ʽ��ֵ����������ϷAI�ĸߵ�  
	 */  
	public   int   gameState ( char []   board ) {   
	       int   result =   INPROGRESS ;   
	       boolean   isFull =   true ;   
	       int   sum = 0;   
	       int   index = 0;   
	       // is game over?   
	       for ( int   pos=0; pos<9; pos++){   
	             char   chess = board[pos];   
	             if ( empty ==chess){   
	                  isFull =   false ;   
	            } else {   
	                  sum += chess;   
	                  index = pos;   
	            }   
	      }   
	         
	       // ����ǳ�ʼ״̬����ʹ�ÿ��ֿ�   
	       boolean   isInitial = (sum== x ||sum== o );   
	       if (isInitial){   
	             return   (sum== x ?1:-1)*INITIAL_POS_VALUE[index];   
	      }   
	         
	       // is Max win/lose?   
	       for ( int [] status :   WIN_STATUS ){   
	             char   chess = board[status[0]];   
	             if (chess== empty ){   
	                  // break ; 
	            	 continue;
	            }   
	             int   i = 1;   
	             for (; i<status.length; i++){   
	                   if (board[status[i]]!=chess){   
	                         break ;   
	                  }   
	            }   
	             if (i==status.length){   
	                  result = chess== x   ?   WIN   :   LOSE ;   
	                   break ;   
	            }   
	      }   
	         
	       if (result!= WIN   & result!= LOSE ){   
	               
	             if (isFull){   
	                   // is draw   
	                  result =   DRAW ;   
	            } else {   
	                   // check double link   
	                   // finds[0]->'x', finds[1]->'o'   
	                   int [] finds =   new   int [2];   
	                   for ( int [] status :   WIN_STATUS ){   
	                         char   chess =   empty ;   
	                         boolean   hasEmpty =   false ;   
	                         int   count = 0;   
	                         for ( int   i=0; i<status.length; i++){   
	                               if (board[status[i]]== empty ){   
	                                    hasEmpty =   true ;   
	                              } else {   
	                                     if (chess== empty ){   
	                                          chess = board[status[i]];   
	                                    }   
	                                     if (board[status[i]]==chess){   
	                                          count++;   
	                                    }   
	                              }   
	                        }   
	                         if (hasEmpty && count>1){   
	                               if (chess== x ){   
	                                    finds[0]++;   
	                              } else {   
	                                    finds[1]++;   
	                              }   
	                        }   
	                  }   
	                     
	                   // check if two in one line   
	                   if (finds[1]>0){   
	                        result = - DOUBLE_LINK ;   
	                  } else  
	                   if (finds[0]>0){   
	                        result =   DOUBLE_LINK ;   
	                  }   
	                     
	            }   
	               
	      }   
	         
	       return   result;   
	} 
	
	
	/**  
	 * ��'x'�ĽǶ������ǵļ�С�����㷨  
	 */  
	public   int   minimax( char [] board,   int   depth){   
	       int [] bestMoves =   new   int [9];   
	       int   index = 0;   
	         
	       int   bestValue = - INFINITY ;   
	       for ( int   pos=0; pos<9; pos++){   
	               
	             if (board[pos]== empty ){   
	                  board[pos] =   x ;   
	                     
	                   int   value = min(board, depth, - INFINITY , + INFINITY );   
	                   if (value>bestValue){   
	                        bestValue = value;   
	                        index = 0;   
	                        bestMoves[index] = pos;   
	                  } else  
	                   if (value==bestValue){   
	                        index++;   
	                        bestMoves[index] = pos;   
	                  }   
	                     
	                  board[pos] =   empty ;   
	            }   
	               
	      }   
	         
	       if (index>1){   
	            index = ( new   Random (System. currentTimeMillis ()).nextInt()>>>1)%index;   
	      }   
	       return   bestMoves[index];   
	         
	}   
	
	
	/**  
	 * ��'O'�ĽǶ������ǵļ�С�����㷨  
	 */  
	public   int   maximin( char [] board,   int   depth){   
	       int [] bestMoves =   new   int [9];   
	       int   index = 0;   
	         
	       int   bestValue =  INFINITY ;   
	       for ( int   pos=0; pos<9; pos++){   
	               
	             if (board[pos]== empty ){   
	                  board[pos] =   o ;   
	                     
	                   int   value = max(board, depth, - INFINITY , + INFINITY );   
	                   if (value<bestValue){   
	                        bestValue = value;   
	                        index = 0;   
	                        bestMoves[index] = pos;   
	                  } else  
	                   if (value==bestValue){   
	                        index++;   
	                        bestMoves[index] = pos;   
	                  }   
	                     
	                  board[pos] =   empty ;   
	            }   
	               
	      }   
	         
	       if (index>1){   
	            index = ( new   Random (System. currentTimeMillis ()).nextInt()>>>1)%index;   
	      }   
	       return   bestMoves[index];   
	         
	}   
	
	/**  
	 * ����'x'����ֵԽ�����Խ����  
	 */  
	public   int   max( char [] board,   int   depth,   int   alpha,   int   beta){   
	         
	       int   evalValue =   gameState (board);   
	         
	       boolean   isGameOver = (evalValue== WIN   || evalValue== LOSE   || evalValue== DRAW );   
	       if (beta<=alpha){   
	             return   evalValue;   
	      }   
	       if (depth==0 || isGameOver){   
	             return   evalValue;   
	      }   
	         
	       int   bestValue = - INFINITY ;   
	       for ( int   pos=0; pos<9; pos++){   
	               
	             if (board[pos]== empty ){   
	                   // try   
	                  board[pos] =   x ;   
	                     
	                   //   maximixing   
	                  bestValue = Math. max (bestValue, min(board, depth-1, Math. max (bestValue, alpha), beta));   
	                     
	                   // reset   
	                  board[pos] =   empty ;   
	            }   
	               
	      }   
	         
	       return   evalValue;   
	         
	}   
	/**  
	 * ����'o'����ֵԽС����Խ����  
	 */  
	public   int   min( char [] board,   int   depth,   int   alpha,   int   beta){   
	         
	       int   evalValue =   gameState (board);   
	         
	       boolean   isGameOver = (evalValue== WIN   || evalValue== LOSE   || evalValue== DRAW );   
	       if (alpha>=beta){   
	             return   evalValue;   
	      }   
	       // try   
	       if (depth==0 || isGameOver || alpha>=beta){   
	             return   evalValue;   
	      }   
	         
	       int   bestValue = + INFINITY ;   
	       for ( int   pos=0; pos<9; pos++){   
	               
	             if (board[pos]== empty ){   
	                   // try   
	                  board[pos] =   o ;   
	                     
	                   //   minimixing   
	                  bestValue = Math.min(bestValue, max(board, depth-1, alpha, Math.min(bestValue, beta)));   
	                     
	                   // reset   
	                  board[pos] =   empty ;   
	            }   
	               
	      }   
	         
	       return   evalValue;   
	         
	}   
	
	/**
	 * ��ȡ���Է�������߷�
	 * @param board	����״̬
	 * @return
	 */
	public int getNextMove(char [] board) {
		
		return minimax(board,3);
	}
	
	public int comp1GetNextMove(char [] board) {
		
		return minimax(board,3);
	}
	public int comp2GetNextMove(char [] board) {
	
	return maximin(board,2);
}
}
