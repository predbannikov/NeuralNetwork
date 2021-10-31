import numpy
import scipy.special
# import json
# import matplotlib.pyplot as plot

#%matplotlib inline



class neuralNetwork:
    #Инициализация сети
    def __init__(self, inputnodes, hiddennodes, outputnodes, learningrate):

    
    



        data_files = open("H:\\projects\\neuralnetwork\\mnist_train.csv", 'r')
        # data_files = open("H:\\projects\\neuralnetwork\\mnist_train.csv", 'r')

        self.data_list = data_files.readlines()
        data_files.close()
        print("size = ", len(self.data_list))
        print( "__init__", 1)


        test_data_file = open("H:\\projects\\neuralnetwork\\mnist_test.csv", 'r')
        # test_data_file = open("H:\\projects\\neuralnetwork\\mnist_test.csv", 'r')
        self.test_data_list = test_data_file.readlines();
        test_data_file.close()


    
    
    
    
    
        #задать колличество узлов во входном, скрытом и выходном слое
        self.inodes = inputnodes
        self.hnodes = hiddennodes
        self.onodes = outputnodes
        
        #коэффициент обучения
        self.lr = learningrate
        
        self.wih = (numpy.random.rand(self.hnodes, self.inodes) - 0.5)
        self.who = (numpy.random.rand(self.onodes, self.hnodes) - 0.5)
        print("wih " , self.wih.shape)
        print("who " , self.who.shape)
        
        #print("Весы входящего скрытого\n", self.wih)
        #print("Весы выходящего скрытого\n",self.who)
        
        self.activation_func = lambda x: scipy.special.expit(x)
        pass
    
    def saveWeight(self, num_epochs):
        print( "saveWeight")
        data = {
            "inputnodes": self.inodes,
            "hiddennodes": self.hnodes,
            "outputnodes": self.onodes
            
        }
        with open("H:\\projects\\neuralnetwork\\option.json", 'w') as outfile:
            json.dump(data, outfile)
    

        numpy.savetxt("H:\\projects\\neuralnetwork\\w1.csv", self.wih, delimiter=",")
        numpy.savetxt("H:\\projects\\neuralnetwork\\w2.csv", self.who, delimiter=",")
        
        

        pass
    
    #Тренировка сети
    def train(self, input_list, targets_list):
        #print( "train")
        inputs = numpy.array(input_list, ndmin = 2).T
        targets = numpy.array(targets_list, ndmin = 2).T
#         print("Входящий сигнал скрытого слоя\n",inputs)
        hidden_inputs = numpy.dot(self.wih, inputs)
#         print("сигнал скрытого слоя\n", hidden_inputs)
        hidden_outputs = self.activation_func(hidden_inputs)
#         print("выходящий сигнал скрытого слоя\n", hidden_outputs)
        
        final_inputs = numpy.dot(self.who, hidden_outputs)
#         print("входящий сигнал для выходного слоя\n", final_inputs)
        final_outputs = self.activation_func(final_inputs)
#         print("Исходящий сигнал для выходного слоя\n", final_outputs)
        
        output_errors = targets - final_outputs
#         print("Ошибки \n", output_errors)
        
        hidden_errors = numpy.dot(self.who.T, output_errors)
        
        self.who += self.lr * numpy.dot((output_errors * final_outputs * (1.0 - final_outputs)), numpy.transpose(hidden_outputs))
        self.wih += self.lr * numpy.dot((hidden_errors * hidden_outputs * (1.0 - hidden_outputs)), numpy.transpose(inputs))
        pass
    
    #Опрос сети
    def query(self, input_list):
        #print( "query")
        inputs = numpy.array(input_list, ndmin = 2).T
#         print("Входящий сигнал скрытого слоя\n",inputs)
        hidden_inputs = numpy.dot(self.wih, inputs)
#         print("сигнал скрытого слоя\n", hidden_inputs)
        hidden_outputs = self.activation_func(hidden_inputs)
#         print("выходящий сигнал скрытого слоя\n", hidden_outputs)
        
        final_inputs = numpy.dot(self.who, hidden_outputs)
#         print("входящий сигнал для выходного слоя\n", final_inputs)
        final_outputs = self.activation_func(final_inputs)
#         print("Исходящий сигнал для выходного слоя\n", final_outputs)
        return final_outputs
        pass
    
    
    
    def test(self, test_list):
        print( "test")
        scorecard = []
        for record in test_list:
            all_values = record.split(',')
            correct_label = int(record[0])
        #     print(correct_label, "истинный маркер")
            inputs = (numpy.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
            outputs = n.query(inputs)
            label = numpy.argmax(outputs)
        #     print(correct_label, "истинный маркер --> ", label, "ответ сети", outputs[label])
        #     if(outputs[label] < 0.3):
        #         print(outputs)
            if(correct_label == label):
                scorecard.append(1)
            else:
                scorecard.append(0)
                pass
            pass
        scorecard_array = numpy.asarray(scorecard)
        print(scorecard_array, scorecard_array.sum())
        result = scorecard_array.sum() / scorecard_array.size
        print("эффективность =", result)
        return result
        pass

    def runing(self):
        print( "runing")

        print(self.inodes)
        print(self.hnodes)
        print(self.onodes)
        #n = neuralNetwork(input_nodes, hidden_nodes, output_nodes, learning_rate)


            # line = data_list[2]
        # print(line);
        # all_values = line.split(',')
        # print("len line = ", len(all_values))
        # image_array = numpy.asfarray(all_values[1:]).reshape((28, 28))
        # plot.imshow(image_array)
        epochs = 1
        res = []
        for e in range(epochs):
            print("эпоха ", e)
            for record in self.data_list:
                all_values = record.split(',')
                inputs = (numpy.asfarray(all_values[1:]) / 255.0 * 0.99) + 0.01
                targets = numpy.zeros(output_nodes) + 0.01
                targets[int(all_values[0])] = 0.99
                n.train(inputs, targets)
                pass
            res.append(self.test(self.test_data_list))
    #         gt = numpy.asarray(res).T
    #         plot.plot(gt)
        #    plot.show()
    #         n.saveWeight(e)
            pass


        pass
    pass
pass
input_nodes = 784
hidden_nodes = 100
output_nodes = 10
learning_rate = 0.3

n = neuralNetwork(input_nodes, hidden_nodes, output_nodes, learning_rate)
n.runing()
