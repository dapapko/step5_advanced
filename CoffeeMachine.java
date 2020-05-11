import java.io.*;
import java.util.HashMap;
import java.util.Map;


public class CoffeeMachine {
    private int temperature;
    private String colour;
    private String model;
    private boolean canMakeCappuccino;
    private int numberOfCups;
    private int price;
    private int pressure;

    private void warm(int temp) {
        while (temperature < temp) {
            temperature++;
            System.out.println("Warming. Current temperature is " + temperature);
        }
    }


    private static int getValue(Map<String, String> m, String key, int def) {
        try {
            return Integer.parseInt(m.get(key));
        } catch (NumberFormatException e) {
            return def;
        }
    }

    public void makeCoffee(boolean hot) {
        System.out.println("The process of making coffee started");
        warm( hot ? 120 : 100);
        System.out.println("Activating pump");
        System.out.println("Deactivating pump");
        System.out.println("Your drink is ready");
    }

    CoffeeMachine(String fname, char delimeter) {
        Map<String, String> data = new HashMap<>(Map.of("temperature", "10", "colour", "black",
                "model", "Vitek VT-1525", "price", "1500",
                "numberOfCups", "2", "canMakeCappuccino", "true", "pressure", "10"));
        try {
            File file = new File(fname);
            FileReader fr = new FileReader(file);
            BufferedReader buffer = new BufferedReader(fr);
            String line, key, val;
            int lineCounter = 0;
            try {
                while ((line = buffer.readLine()) != null && lineCounter < 6) {
                    try {
                        key = line.substring(0, line.indexOf(delimeter));
                        val = line.substring(line.indexOf(delimeter) + 1);
                        data.put(key, val);
                        lineCounter++;
                    } catch (StringIndexOutOfBoundsException e) {
                        System.out.println("Warning. Incorrect token! ");
                    }
                }
            } catch (IOException e) {
                System.out.println("IO error. Initializaing with default values.");
            }
        } catch (FileNotFoundException e) {
            System.out.println("Unable to find file. Initializaing with default values.");
        }

        temperature = getValue(data, "temperature", 20);
        numberOfCups = getValue(data, "numberOfCups", 2);
        price = getValue(data, "price", 2000);
        pressure = getValue(data, "pressure", 10);
        canMakeCappuccino = data.get("canMakeCappuccino").equals("true");
        model = data.get("model");
        colour = data.get("colour");
    }


    @Override
    public String toString() {
        return String.format("Temperature: %d Colour: %s Model: %s Number of cups: %d Price: %d Pressure: %d", temperature, colour, model, numberOfCups, price, pressure);
    }

}

