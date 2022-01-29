import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
import java.lang.Math;

public class ECC {

    static int[] e_gcd(int a,int b)
    {
        if(b == 0)
        {
            return new int[] {a,1,0};
        }
        else
        {
            int[] arr = e_gcd(b,a%b);
            int gcd = arr[0];
            int x = arr[2];
            int y = arr[1] - (a/b)*arr[2];

            return new int[] {gcd,x,y};
        }
    }

    static int mod_inv(int a, int m) {

        int[] arr = e_gcd(a, m);

        if (arr[0] != 1)
            return 0;
        if (arr[1] > 0)
            return arr[1];
        else
            return arr[1] + m;
    }

    static int[] cal(int x1,int y1,int x2,int y2,int[] E)
    {
        int a,b,p;
        a = E[0];
        b = E[1];
        p = E[2];

        if(x1 == x2 && y1 == y2)
        {
            int xr1,yr1,m;

            m = Math.floorMod((((3*x1*x1) + a)*(mod_inv(2*y1,p))),p);

            xr1 = Math.floorMod(((m*m) - (2*x1)),p);
            yr1 = Math.floorMod((m*(x1-xr1) - y1),p);

            return new int[] {xr1,yr1};
        }
        else{
            int xr2,yr2,m;
            if(x2-x1 < 0)
            {
                m = Math.floorMod((-(y2-y1)*(mod_inv(Math.abs(x2-x1),p))),p);
            }
            else{
                m = Math.floorMod(((y2-y1)*(mod_inv(Math.abs(x2-x1),p))),p);
            }

            xr2 = Math.floorMod(((m*m) - x1 - x2),p);
            yr2 = Math.floorMod((m*(x1-xr2) - y1),p);

            return new int[] {xr2,yr2};
        }
    }

    static int[] point(int a,int b,int p,int x,int y,int k)
    {
        if(k==1)
        {
            return new int[] {x,y};
        }
        if(k>=2)
        {
            int[] point1 = {x,y};
            int[] point2;

            //G2
            point1 = cal(point1[0],point1[1],x,y,new int[] {a,b,p});
            k = k-2;

            while (k!=0)
            {
                point1 = cal(point1[0],point1[1],x,y,new int[] {a,b,p});
                k = k-1;
            }
            return point1;
        }
        return new int[] {0,0};
    }

    public static void main(String[] args) {
        int a,b,p,x1,y1;

        Scanner in = new Scanner(System.in);

        System.out.print("a : ");
        a = in.nextInt();

        System.out.print("b : ");
        b = in.nextInt();

        System.out.print("P : ");
        p = in.nextInt();

        System.out.println("\nEnter G point");

        System.out.print("x : ");
        x1 = in.nextInt();

        System.out.print("y : ");
        y1 = in.nextInt();


        Random rand = new Random();
        int xa =rand.nextInt(p-2) + 1;
        int xb =rand.nextInt(p-2) + 1;
        int[] Pa = point(a,b,p,x1,y1,xa);
        int[] Pb = point(a,b,p,x1,y1,xb);

        System.out.println("\nPoint " + xa + "G" + " : " + Arrays.toString(Pa));
        System.out.println("Point " + xb + "G" + " : " + Arrays.toString(Pb));

        int k = rand.nextInt(p-2) + 1;

        System.out.println("\nK = " + k);
        int[] M = {0,0};

        System.out.print("\nEnter Plaintext M (x,y)");
        System.out.print("\nx : ");
        M[0] = in.nextInt();

        System.out.print("y : ");
        M[1] = in.nextInt();
        int[][] Pc = {{0,0},{0,0}};
        int[] kB = point(a,b,p,x1,y1,k);
        Pc[0][0] = kB[0];
        Pc[0][1] = kB[1];
        int[] kPb = point(a,b,p,Pb[0],Pb[1],k);
        int[] c2 = cal(M[0],M[1],kPb[0],kPb[1], new int[] {a,b,p});
        Pc[1][0] = c2[0];
        Pc[1][1] = c2[1];

        System.out.println("\nCiphertext : " + Arrays.deepToString(Pc));
        int[] nb_c1 = point(a,b,p,Pc[0][0],Pc[0][1],xb);
        int[] temp2 = cal(Pc[1][0],Pc[1][1],nb_c1[0],-nb_c1[1],new int[] {a,b,p});

        System.out.println("\nDecrypted Plaintext : " + Arrays.toString(temp2));
    }
}
