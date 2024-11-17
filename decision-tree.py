import pandas as pd                                                                                                                                                     

from sklearn.tree import DecisionTreeClassifier ,export_text, plot_tree                                                                                                

from sklearn import metrics                                                                                                                                            

from sklearn import tree                                                                                                                                               

import matplotlib.pyplot as plt                                                                                                                                        



data = {                                                                                                                                                               

    'x1': [1,1,1,1,1,0,0,1,0,1],                                                                                                                                       
    'x2': [1,0,0,0,1,1,0,0,1,0],                                                                                                                                       
    'x3': [1,1,0,0,1,1,0,1,0,0],                                                                                                                                       

    'y' : [1,1,0,0,1,0,0,1,1,0]                                                                                                                                        
}                                                                                                                                                                      



df = pd.DataFrame(data)                                                                                                                                                





X = df[['x1', 'x2', 'x3']]                                                                                                                                             

y = df['y']                                                                                                                                                            



clf = DecisionTreeClassifier(criterion = 'entropy',)                                                                                                                   




clf = clf.fit(X, y)                                                                                                                                                    





plt.figure(figsize=(12, 8))                                                                                                                                            

tree.plot_tree(clf, feature_names=['x1','x2','x3'], class_names=['1', '0'], filled=True)                                                                               

plt.show()                                                                                                                                                             
                                                                                                                                                                       
tree_rules = export_text(clf, feature_names=['x1', 'x2', 'x3'])                                                                                                        

print("\nDecision Tree Rules:")                                                                                                                                        

print(tree_rules)                                                                                                                                                      
                                                                                                                                                                       
import numpy as np                                                                                                                                                     

                                                                                                                                                                       
def prob(y):                                                                                                                                                           
    count1=0                                                                                                                                                           
    for i in y:                                                                                                                                                        
        if i==1:                                                                                                                                                       
            count1+=1                                                                                                                                                  
    return count1/len(y)                                                                                                                                               

def entropy(data):                                                                                                                                                     
    p1=prob(data)                                                                                                                                                      
    print(p1)                                                                                                                                                          
    if p1==0 or p1==1:                                                                                                                                                 
        return 0                                                                                                                                                       
    s1=-p1*np.log2(p1)                                                                                                                                                 

    s2=-(1-p1)*np.log2((1-p1))                                                                                                                                         


    s = s1+s2                                                                                                                                                          

    return s                                                                                                                                                           



en = entropy(y)                                                                                                                                                        

print(en)                                                                                                                                                              
                                                                                                                                                                       
                                                                                                                                                                       
def splitdata(x,indices,feature):                                                                                                                                      
    left=[]                                                                                                                                                            
    right=[]                                                                                                                                                           
    for i in range(indices):                                                                                                                                           
        if(x[feature][i]==1):                                                                                                                                          
            left.append(i)                                                                                                                                             
        else:                                                                                                                                                          
            right.append(i)                                                                                                                                            

    return left,right                                                                                                                                                  
                                                                                                                                                                       
                                                                                                                                                                       
                                                                                                                                                                       
l1,r1=splitdata(data,10,'x1')                                                                                                                                          
l2,r2=splitdata(data,10,'x2')                                                                                                                                          
l3,r3=splitdata(data,10,'x3')                                                                                                                                          
print(l1,r1)                                                                                                                                                           
print(l2,r2)                                                                                                                                                           
print(l3,r3)                                                                                                                                                           
                                                                                                                                                                       
                                                                                                                                                                       
def infogain(left,right):                                                                                                                                              

    temp1=[]                                                                                                                                                           

    temp2=[]                                                                                                                                                           

    for i in left:                                                                                                                                                     

        temp1.append(y[i])                                                                                                                                             

    for i in right:                                                                                                                                                    

        temp2.append(y[i])                                                                                                                                             

    return entropy(y) - (prob(temp1) * (entropy(temp1)) + prob(temp2) * (entropy(temp2)))                                                                              








f1=infogain(l1,r1)                                                                                                                                                     

f2=infogain(l2,r2)                                                                                                                                                     

f3=infogain(l3,r3)                                                                                                                                                     

print(f1,f2,f3)                                                                                                                                                        




def best_split(f1,f2,f3):                                                                                                                                              

    if f1>f2 and f1>f3:                                                                                                                                                

        return 1                                                                                                                                                       

    return 2 if f2>f3 else 3                                                                                                                                           
                                                                                                                                                                       
best_split(f1,f2,f3)                                                                                                                                                   
                        
