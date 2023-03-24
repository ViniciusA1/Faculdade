package org.project.poo;

public class Account {
        private final int agency = 1;
        private int accountNum;
        private static int count = 0;
        private String name;
        private double balance;
        
        public Account() {
                count++;
                accountNum = count;
        }

        public Account(String name) {
                this();
                this.name = name;
        }

        public Account(double value) {
                this();
                balance = value;
        }

        public Account(String name, double value) {
                this(name);
                balance = value;
        }

        public void setName(String name) {
                this.name = name;
        }

        public String getName() {
                return name;
        }

        public void setBalance(double amount) {
                balance = amount;
        }

        public double getBalance() {
                return balance;
        }

        public int getAgency() {
                return agency;
        }

        public int getAccountNum() {
                return accountNum;
        }

        public int getAccountAmount() {
                return count;
        }

        public void depositCash(double amount) {
                if(amount > 0)
                        balance += amount;
        }

        public void withdrawCash(double amount) {
                if(amount > 0 && balance - amount >= 0)
                        balance -= amount;
        }
}
