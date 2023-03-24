package org.project.poo;
import java.util.Scanner;

class ReadName {
	public static void main(String[] args) {
		Scanner read = new Scanner(System.in);
		String name;

		System.out.print("Digite um nome: ");
		name = read.nextLine();

		System.out.println("O nome é: " + name);
		read.close();
	}
}
