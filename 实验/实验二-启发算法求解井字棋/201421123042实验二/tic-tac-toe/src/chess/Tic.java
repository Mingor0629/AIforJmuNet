package chess;

import java.util.Scanner;

public class Tic {
	
	Scanner sc = new Scanner(System.in);
	private char[] chess = new char[9];
	private Algorithm al = new Algorithm();
	
	
	public char[] getChess() {
		return chess;
	}

	public void setChess(char[] chess) {
		this.chess = chess;
	}

	/**
	 * ��ʼ������
	 */
	public void initBroad() {
		for(int i=0;i<chess.length;i++) {
			chess[i] = ' ';
		}
		
		
	}
	
	/**
	 * ��ӡ����
	 */
	public void printBroad() {
		
		System.out.println("-------------------------");
		System.out.println("|       |       |       |");
		for(int i=0;i<chess.length;i++) {
			if(i%3==0&&i!=0) {
				System.out.println("|");
				System.out.println("|       |       |       |");
				System.out.println("-------------------------");
				System.out.println("|       |       |       |");
			}
			
			System.out.print("|   "+chess[i]+"   ");
			
			
		}
		System.out.println("|");
		System.out.println("|       |       |       |");
		System.out.println("-------------------------");
		
		
	}
	
	/**
	 * �жϸ�λ���Ƿ�������
	 * @param i	����λ��
	 * @return	
	 */
	public boolean isEmpty(int i) {
		
		return chess[i] == ' ';
		
	}
	
	
	/**
	 * ��ȡ�����������
	 * @return
	 */
	public int getPos() {
		boolean flag = true;
		int pos = 0;
		System.out.println("�ֵ���Ļغϡ���");
		while(flag) {
			System.out.println("���������ѡ������֮���Կո�ֿ������磺2 2��");
			int m = sc.nextInt();
			int n = sc.nextInt();
			if(m<0||m>3||n<0||n>3) {
				System.out.println("�����������������룡");
			}else {
				pos = (m-1)*3+n-1;
				if(isEmpty(pos)==true) {
					flag=false;
				}else {
					
					System.out.println("�ø��Ѿ������ӣ�����������");
				}
				
			}
			
		}
		
		return pos;
		
	}
	
	/**
	 * ѡ������˳��
	 * @return
	 */
	public int chooseFirstPlace() {
		boolean flag=true;
		
		System.out.println("��ѡ������˳��1��������֣�2���������֣���");
		int choose = sc.nextInt();
		while(flag) {
			if(choose==1||choose==2) {
				flag = false;
			}else {
				System.out.println("��������ȷ���֣�");
			}
		}
		
		return choose;
		
	}
	
	/**
	 * ����غ�
	 */
	public void humanPlace() {
		int pos = getPos();
		chess[pos] = 'O';
		System.out.println("�������");
		printBroad();
	}
	
	

	/**
	 * ���Իغ�
	 */
	public void comPlace() {
		int pos = al.getNextMove(chess);
		//pos = (m-1)*3+n-1;
		System.out.println("�ֵ����Իغϣ����Ե�ѡ����:"+(pos/3+1)+" "+(pos%3+1));
		chess[pos] = 'X';
		System.out.println("�������");
		printBroad();
	}
	
	/**
	 * ����1�غ�
	 */
	public void com1Place() {
		int pos = al.comp1GetNextMove(chess);
		System.out.println("�ֵ�������Ȼ�����һغϣ����Ե�ѡ����:"+(pos/3+1)+" "+(pos%3+1));
		chess[pos] = 'X';
		System.out.println("�������");
		
	}
	
	/**
	 * ����2�غ�
	 */
	public void com2Place() {
		int pos = al.comp2GetNextMove(chess);
		System.out.println("�ֵ�������Ȼ�����һغϣ����Ե�ѡ����:"+(pos/3+1)+" "+(pos%3+1));
		chess[pos] = 'O';
		System.out.println("�������");
		
	}
	
	
	
	
	
	
	
	
	
}
