public class Sample {
    public static void main(String[] args) {
        CoffeeMachine machine = new CoffeeMachine("coffee.txt", '|');
        CoffeeMachine machine2 = new CoffeeMachine(machine);
        System.out.println(machine);
        System.out.println(machine2);
        machine.makeCoffee(true);

    }
}
