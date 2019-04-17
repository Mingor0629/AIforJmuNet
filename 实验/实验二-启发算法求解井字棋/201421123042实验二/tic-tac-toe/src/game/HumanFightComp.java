package game;
import java.util.*;
import chess.*;


public class HumanFightComp {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String newGame;
		int choose;
		Algorithm al = new Algorithm();
		Tic tic = new Tic();
		
		boolean flag=true;
		while(flag) {
			tic.initBroad();
			choose = tic.chooseFirstPlace();
			if(choose==2) {
				tic.comPlace();
			}
			while(true) {
				tic.humanPlace();
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
				tic.comPlace();
				//System.out.println(al.gameState(tic.getChess()));
				if(al.gameState(tic.getChess())==al.WIN || al.gameState(tic.getChess())==al.LOSE || al.gameState(tic.getChess())==al.DRAW) {
					break;
				}
			}
			if(al.gameState(tic.getChess())==al.WIN) {
				System.out.println("���ź��������ˣ����ٽ�����~");
			}else if(al.gameState(tic.getChess())==al.LOSE) {
				System.out.println("��ϲ��սʤ�˵��ԣ�");
			}else {
				System.out.println("��ϲ������Դ��ƽ�֣�");
			}
			System.out.println("�Ƿ�ʼһ������Ϸ��y:�ǣ�n:�񣩣�");
			newGame = sc.next();
			if(newGame.equalsIgnoreCase("n")) {
				flag=false;
			}
		}
		

	}

}
