import numpy as np
import matplotlib.pyplot as plt

plt.rcParams.update({'font.size': 20})
plt.figure(figsize=(15,9))

n = 15 # количество экспериментов в серии

N = np.array([])
Nquad = np.array([])
dN = np.array([])

I = np.array([])
Iquad = np.array([])
dI = np.array([])

# загрузка первой серии
string = input()
for ind, val in enumerate(string.split()):
    val = int(val);
    if (ind % 2 == 0):
        N = np.append(N, val)
        Nquad = np.append(Nquad, val**2)
    else:
        I = np.append(I, val)
        Iquad = np.append(Iquad, val**2)

# загрузка остальных серий
for i in range(n-1):
    string = input()
    for ind, val in enumerate(string.split()):
        val = int(val);
        if (ind % 2 == 0):
            N[ind//2] += val
            Nquad[ind//2] += val**2
        else:
            I[ind//2] += val
            Iquad[ind//2] += val**2

# усреднение и нахождение погрешностей прямых измерений
N = N / n
I = I / n
Nquad = Nquad / n
Iquad = Iquad / n
dN = ((Nquad - N**2) / (n-1))**0.5
dI = ((Iquad - I**2) / (n-1))**0.5

# взятие логарифма
dN = dN / N
dI = dI / I
N = np.log(N)
I = np.log(I)

plt.scatter(N, I, c='r')
#plt.errorbar(N, I, xerr = dN, yerr=dI, linestyle = 'none')
p,v = np.polyfit(N, I, deg=1, cov=True)
f=np.poly1d(p)
z=np.linspace(N[0],N[-1],1000)
plt.plot(z,f(z))

plt.grid(True)
plt.xlabel(r'$ln(N)$')
plt.ylabel(r'$ln\left(\dfrac{t}{1 нс}\right)$')
plt.title(r'Зависимость ln(t)(ln(N)) для статистического массива')

print(p, v)
plt.show()


