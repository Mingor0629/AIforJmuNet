package game;
import chess.*;

public class CompFightComp {

	public static void main(String[] args) {
		int c1 = 0;
		int c2 = 0;
		int pin = 0;
		Algorithm al = new Algorithm();
		Tic tic = new Tic();
		System.out.println("������Ȼ���������������");
		for(int i=0;i<25;i++) {
			tic.initBroad();
			while(true) {
				tic.com1Place();
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
				tic.com2Place();
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
				
				
			}
			if(al.gameState(tic.getChess())==al.WIN) {
				System.out.println("��ʤ����������ȵĵ������");
				System.out.println("-------------------------");
				c1++;
			}else if(al.gameState(tic.getChess())==al.LOSE) {
				System.out.println("��ʤ���Ƕ�����ȵĵ������");
				System.out.println("-------------------------");
				c2++;
			}else {
				System.out.println("��λ��Ҵ�ƽ");
				System.out.println("-------------------------");
				pin++;
			}
			
			
		}
		
		
		System.out.println("������Ȼ���������������");
		for(int i=0;i<25;i++) {
			tic.initBroad();
			while(true) {
				tic.com2Place();
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
				tic.com1Place();
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
				
				
			}
			if(al.gameState(tic.getChess())==al.WIN) {
				System.out.println("��ʤ����������ȵĵ������");
				System.out.println("-------------------------");
				c1++;
			}else if(al.gameState(tic.getChess())==al.LOSE) {
				System.out.println("��ʤ���Ƕ�����ȵĵ������");
				System.out.println("-------------------------");
				c2++;
			}else {
				System.out.println("��λ��Ҵ�ƽ");
				System.out.println("-------------------------");
				pin++;
			}
			
		}
		
		System.out.println("��Ϸ�����");
		System.out.println("������ȵĵ�����һ�ʤ����Ϊ"+c1);
		System.out.println("������ȵĵ�����һ�ʤ����Ϊ"+c2);
		System.out.println("����������ƽ�Ĵ���Ϊ"+pin);

		
		
	}

}
