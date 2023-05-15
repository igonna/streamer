import time

output_file = 'indata.txt'

num = 0;
while True:
    with open(output_file, 'a') as file:
        num = num + 1;
        file.write(str(num) + '\n')
        time.sleep(1)