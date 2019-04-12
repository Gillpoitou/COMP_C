int factorielle(int a){
    if(a==1){
        return a;
    }else{
        return factorielle(a-1)*a;
    }
}

int main(){
 return factorielle(5);
}