import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
import math
import tensorflowjs as tfjs

import cv2
import os
import glob

from PIL import Image

from tensorflow.python import keras
from tensorflow.python.keras.models import Sequential, Model
from tensorflow.python.keras.layers import InputLayer, Input
from tensorflow.python.keras.layers import Reshape, MaxPooling2D,UpSampling2D
from tensorflow.python.keras.layers import Conv2D, Dense, Flatten
from tensorflow.python.keras.models import load_model
from keras import regularizers
from keras import optimizers
from keras import backend as K


img_dir_train = "/home/srija/tensorflow/-45Images/train_images" # Enter Directory of all images 
img_dir_train_f = "/home/srija/tensorflow/-45Images/frontal" # Enter Directory of all images 
# img_dir_test = "/home/srija/tensorflow/-45Images/random " # Enter Directory of all images
img_dir_test = "/home/srija/tensorflow/-45Images/test_images"

data_path_train = os.path.join(img_dir_train,'*g')
data_path_train_f = os.path.join(img_dir_train_f,'*g')
data_path_test = os.path.join(img_dir_test,'*g')

num_random= 22
image_size = 128    
num_test = 86
num_train = 5
num_persons = 12
total_test = 144

files = glob.glob(data_path_train)
data = []
for f1 in files:
    image = cv2.imread(f1)
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    img = cv2.resize(img, (image_size,image_size))
    #img = np.array(img)
    #img = np.reshape(img, (28*28, 1))
    data.append(img)

train_data = data
train_data = np.array(train_data)   
print(train_data.shape)
train_data = np.reshape(train_data, (num_random, image_size, image_size))
print(train_data.shape)

td_random = []

for i in range(num_train):
    td = [[0]*image_size]*image_size
    idx = np.asscalar(np.random.randint(num_random, size=1))
    idx1 = np.asscalar(np.random.randint(num_random, size=1))
    idx2 = np.asscalar(np.random.randint(num_random, size=1))
    p = [[0]*image_size]
    p = (train_data[idx,:,:] + train_data[idx1,:,:] )/2
    # for j in range(image_size):
    #     for k in range(image_size):
            # print(j)
            # print(k)
            # print(idx)
            # print(train_data[idx][j][k])
            #td[j][k] = train_data[idx][j][k]
    td_random.append(p)
td_random = np.array(td_random)
print(td_random.shape)
td_random = np.reshape(td_random, (num_train,image_size,image_size))
print(td_random.shape)


files = glob.glob(data_path_test)
data = []
for f1 in files:
    image = cv2.imread(f1)
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    img = cv2.resize(img, (image_size,image_size))
    data.append(img)

test_data = data
test_data = np.array(test_data)
test_data = np.reshape(test_data, (total_test, image_size, image_size))
print(test_data.shape)
new_image_size = 128

# for k in range(num_persons):
#     c1 = k * num_train + 1
#     c2 = c1 + num_train - 1
#     print("c1,c2:", c1, c2)
#     files = glob.glob(data_path_train_f)
#     data = []
#     count = 0
#     for f1 in files:
#         count = count +1
#         if c1<=count<=c2:
#             image = cv2.imread(f1)
#             img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#             img = cv2.resize(img, (new_image_size,new_image_size))
#             #img = np.array(img)
#             #img = np.reshape(img, (28*28, 1))
#             data.append(img)
        

#     train_data = data
#     train_data = np.array(train_data)   
#     print(train_data.shape)
#     train_data = np.reshape(train_data, (num_train, new_image_size, new_image_size))
#     print(train_data.shape)


#     print("Size of:")
#     print("- Training-set:\t\t{}".format(len(train_data)))
#     print("- Test-set:\t{}".format(len(td_random)))


#     input_img = Input(shape=(image_size, image_size, 1))  # adapt this if using `channels_first` image data format

#     x = Conv2D(8, (3, 3), activation='relu', padding='same')(input_img)
#     x = MaxPooling2D((2, 2), padding='same')(x)
#     x = Conv2D(12, (2, 2), activation='relu', padding='same')(x)
#     x = MaxPooling2D((2, 2), padding='same')(x)
#     x = Conv2D(1, (5, 5), activation='relu', padding='same')(x)
#     x = UpSampling2D((2, 2))(x)
#     x = Conv2D(16, (2, 2), activation='relu', padding='same')(x)
#     x = UpSampling2D((2, 2))(x)
#     x = Conv2D(1, (5, 5), activation='relu', padding='same')(x)


#     autoencoder = Model(input_img, x)
#     print(autoencoder.summary())
#     from tensorflow.python.keras.optimizers import Adam
#     optimizer = Adam(lr = 1e-3)
#     autoencoder.compile(keras.optimizers.SGD(lr=0.05), loss='mean_squared_error',
#     metrics=['accuracy'])

#     train_data = train_data.astype('float32') / 255.
#     td_random = td_random.astype('float32') / 255.
#     test_data = test_data.astype('float32') / 255.
#     train_data = np.reshape(train_data, (len(train_data), new_image_size, new_image_size, 1))  # adapt this if using `channels_first` image data format
#     td_random = np.reshape(td_random, (len(td_random), image_size, image_size, 1))  # adapt this if using `channels_first` image data format
#     test_data = np.reshape(test_data, (len(test_data), image_size, image_size, 1))  # adapt this if using `channels_first` image data format

#     from keras.callbacks import TensorBoard


#     autoencoder.fit(td_random, train_data,
#                         epochs=300,
#                         batch_size=5,
#                         shuffle=True,
#                         )
#     #     # encode and decode some digits
#         # note that we take them from the *test* set

#     path_model = '/home/srija/tensorflow/-45Images/models_new/model_new_'+str(k)+'.keras'

#     autoencoder.save(path_model)

# for i in range(num_test):
new_test_num= total_test
test_2 = test_data[0:new_test_num]
for j in range(num_persons):
    path_model = '/home/srija/tensorflow/-45Images/models_new/model_new_'+str(j)+'.keras'
    model2 = load_model(path_model)
    encoded_image = test_data
    encoded_image = np.reshape(test_2,(None,new_test_num,image_size,image_size))
    decoded_image = model2.predict(encoded_image)

    img = encoded_image
    #img = cv2.resize(img, (new_test_num,image_size,image_size))
    img = np.array(img)
    img = np.reshape(img, (image_size*image_size, new_test_num))
    #test_data[i] = np.reshape(test_data[i], (784,1))
    np.savetxt("/home/srija/tensorflow/-45Images/output_all/ori/ori_"+str(j)+".txt", img)


    # save reconstruction
    img = decoded_image
    #img = cv2.resize(img, (new_test_num,new_image_size,new_image_size))
    img = np.array(img)
    img = np.reshape(img, (new_image_size*new_image_size, new_test_num))
    #decoded_imgs[i] = np.reshape(decoded_imgs[i], (784,1))
    np.savetxt("/home/srija/tensorflow/-45Images/output_all/res/res_"+str(j)+".txt", img)
