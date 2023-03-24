echo "what's the Main class? (default: Main)"
read MAIN_CLASS
if [[ $MAIN_CLASS = "" ]]; then 
    MAIN_CLASS=Main
fi
mvn clean package && clear && \
    java -cp target/classes org.project.poo.$MAIN_CLASS
