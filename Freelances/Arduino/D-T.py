import serial
import matplotlib.pyplot as plt

# Seri port ayarları
ser = serial.Serial('COM1', 9600) # Port ismi ve baudrate değeri burada belirtilir

# Grafik ayarları
plt.ion() # Canlı grafik modunu açar
plt.xlabel('Zaman (s)') # X ekseni etiketi
plt.ylabel('Uzaklık (cm)') # Y ekseni etiketi
plt.grid(True) # Izgara çizimini açar

# Verileri tutacak değişkenler
x_data = []
y_data = []

# Grafik çizimi
fig = plt.figure()
ax = fig.add_subplot(111)
line, = ax.plot(x_data, y_data, 'r-')

# Veri okuma ve grafik güncelleme döngüsü
while True:
    try:
        # Seri porttan veri okuma
        data = ser.readline().decode().strip() # Veriyi okurken "\n" karakteri ve diğer gereksiz karakterler temizleniyor
        distance = float(data) # Veriyi float tipine dönüştürür
        print(distance) # Okunan veriyi ekrana yazdırır
        
        # Verileri listelere ekleme
        x_data.append(len(x_data))
        y_data.append(distance)
        
        # Grafik güncelleme
        line.set_xdata(x_data)
        line.set_ydata(y_data)
        ax.relim()
        ax.autoscale_view(True,True,True)
        plt.draw()
        plt.pause(0.01)
        
    except KeyboardInterrupt:
        break

# Seri port bağlantısını kapatma
ser.close()
