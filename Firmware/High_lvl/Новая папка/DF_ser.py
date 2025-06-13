import serial
import struct
import time
from crc import Calculator, Crc8  # Установите библиотеку: pip install crc

class SerialTransmitter:
    def __init__(self, port='/dev/ttyUSB0', baudrate=115200):
        self.ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Порт {port}, запущен")
        self.calculator = Calculator(Crc8.CCITT)
        time.sleep(0.5)  # Ожидание инициализации Arduino
        
    def read(self):
        if self.ser.in_waiting >= 5:
            while (self.ser.in_waiting > 0):
                    receive = self.ser.readline().decode('utf-8')
            return 1, receive
        else:
            return 0, ""

    def send(self, value1 =282, value2 = 282, value3 = 282, max_retries=5):
        
       
        data = struct.pack('<hhh', value1, value2, value3)  # 6 байт данных
        
        crc = self.calculator.checksum(data)# Рассчитываем CRC8 
        packet = data + bytes([crc])  # Итоговый пакет: 7 байт

        self.ser.write(packet)
        self.ser.write(packet)
        self.ser.write(packet)

        '''for attempt in range(max_retries): # Попытки передачи
            try:
                self.ser.write(packet)
                
                             
                # Ждем подтверждения (1 байт)
                response = self.read()
                if  __name__ == "__main__":
                    if  b'\x06' in response:  # ACK
                        return True
                    elif response == b'\x15':  # NAK
                        print("Err CRC")
                        continue
                    else:
                        print("Serial timeout")
                        continue
                    
            except Exception as e:
                print(f"Err to send")
                continue
                
        print(f"Not work")
        return False
        '''

    def close(self):
        self.ser.close()

if __name__ == "__main__":
    try:
        main_atm = SerialTransmitter(port='/dev/ttyUSB0')
    except:
        main_atm = SerialTransmitter(port='/dev/ttyUSB1')
    
    try:
        while True:
            print("\nТест Serial")
            n = int(input("Сколько данных "))
            dat = [0,0,0]
            for i in range (n):
                dat[i] = int(input(f"{i+1}: "))           
            
            main_atm.send(dat[0], dat[1], dat[2])
                
    except KeyboardInterrupt:
        print("\nПрограмма завершена")
    finally:
        main_atm.close()