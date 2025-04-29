echo "Enter the number of rows:"
read n

echo -e "Triangle star here lalalalala :"
for ((i = 1; i <= n; i++)); 
do
    for ((j = 1; j <= i; j++)); 
    do
        echo -n "$j "
    done
    echo
done