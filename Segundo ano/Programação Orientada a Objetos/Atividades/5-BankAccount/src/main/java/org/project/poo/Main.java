package org.project.poo;

public class Main {
        private static final int MAXACCOUNT = 100;

        public static void main(String[] args) {
                Account[] accountArray = new Account[MAXACCOUNT];
                boolean isRunning = true;
                int userOpt = 0, accountChosen = 0;

                accountArray[0] = new Account();

                while(isRunning) {
                        accountChosen = Menu.chooseAccountMenu(accountArray);
                        userOpt = Menu.mainMenu();
                        isRunning = Menu.verifyUserInput(accountArray[accountChosen], userOpt);
                }

                accountArray = null;
        }
}
