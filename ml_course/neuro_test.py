import numpy as np 

def get_weights(x, y):
    step1 = np.linalg.inv(x.T.dot(x))
    step2 = step1.dot(x.T)
    return step2.dot(y)


def predict(row, weights):
    sum_ = row.dot(weights.T)
    if sum_ > 0:
        return 1
    return 0


def target(row ,y):
    if row[1] == 1 and row[2] == 0.3:
        return y[0]
    if row[1] == 0.4 and row[2] == 0.5:
        return y[1]
    return y[2]

def perceptron(x, y, w):
    perfect = False 
    while not perfect:
        perfect = True 
        for e in x:
            prediction = predict(e, w)
            if  prediction != target(e, y):
                perfect = False
                if prediction == 0:
                    w += e
                else:
                    w -= e
    return w 


if __name__ == '__main__':

    x = np.array(
        [
            [1, 1, 0.3],
            [1, 0.4, 0.5],
            [1, 0.7, 0.8]
        ]
    )

    y = np.array(
        [
            [1], [1], [0]
        ]
    )

    w = np.zeros((1, 3))
    final_weights = perceptron(x, y, w)
    
    print(f'Final weights: {final_weights}')

