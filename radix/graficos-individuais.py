import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import numpy as np

def read_data_file(filename):
    """Lê o arquivo de dados e retorna um DataFrame formatado"""
    # Lê o arquivo com as colunas apropriadas
    df = pd.read_csv(filename, header=None)
    
    # Define os nomes das colunas
    df.columns = ['Ordenado', 'Inverso', 'Aleatório']
    
    # Adiciona uma coluna com o tamanho da entrada
    df['Tamanho'] = [100, 1000, 10000, 100000]
    
    return df

def calculate_complexity_curves(sizes, tempo_df):
    """Calcula as curvas de complexidade teóricas"""
    # Obtém o tempo médio para n=100 como referência para escalar as curvas teóricas
    tempo_base = tempo_df.iloc[0][['Ordenado', 'Inverso', 'Aleatório']].mean()
    
    # Calcula os fatores de escala para cada complexidade
    scale_linear = tempo_base / 100  # O(n)
    scale_nlogn = tempo_base / (100 * np.log2(100))  # O(n log n)
    scale_quadratic = tempo_base / (100 * 100)  # O(n²)
    
    # Calcula as curvas teóricas
    curves = {
        'O(n)': [scale_linear * n for n in sizes],
        'O(n log n)': [scale_nlogn * (n * np.log2(n)) for n in sizes],
        'O(n²)': [scale_quadratic * (n * n) for n in sizes]
    }
    
    return curves

def create_plot(movimentacoes_df, tempo_df, comparacoes_df):
    """Cria os gráficos para cada métrica"""
    # Cria um subplot com 3 gráficos
    fig = make_subplots(
        rows=3, cols=1,
        subplot_titles=('Movimentações', 'Tempo de Execução (com Complexidades Teóricas)', 'Comparações'),
        vertical_spacing=0.15
    )
    
    # Lista de cores para cada tipo de entrada
    colors = ['blue', 'red', 'green']
    
    # Tipos de entrada
    entrada_tipos = ['Ordenado', 'Inverso', 'Aleatório']
    
    # Para cada tipo de entrada, adiciona uma linha em cada gráfico
    for i, tipo in enumerate(entrada_tipos):
        # Gráfico de Movimentações
        fig.add_trace(
            go.Scatter(
                x=movimentacoes_df['Tamanho'],
                y=movimentacoes_df[tipo],
                name=f'{tipo} (Movimentações)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=1, col=1
        )
        
        # Gráfico de Tempo
        fig.add_trace(
            go.Scatter(
                x=tempo_df['Tamanho'],
                y=tempo_df[tipo],
                name=f'{tipo} (Tempo)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=2, col=1
        )
        
        # Gráfico de Comparações
        fig.add_trace(
            go.Scatter(
                x=comparacoes_df['Tamanho'],
                y=comparacoes_df[tipo],
                name=f'{tipo} (Comparações)',
                line=dict(color=colors[i]),
                showlegend=True
            ),
            row=3, col=1
        )

    # Adiciona as curvas de complexidade teóricas
    sizes = np.linspace(100, 100000, 1000)
    complexity_curves = calculate_complexity_curves(sizes, tempo_df)
    
    # Cores para as curvas de complexidade
    complexity_colors = {
        'O(n)': 'rgba(128, 128, 128, 0.5)',
        'O(n log n)': 'rgba(255, 165, 0, 0.5)',
        'O(n²)': 'rgba(255, 0, 0, 0.5)'
    }
    
    # Adiciona cada curva de complexidade ao gráfico de tempo
    for complexity_name, curve in complexity_curves.items():
        fig.add_trace(
            go.Scatter(
                x=sizes,
                y=curve,
                name=f'Teórico {complexity_name}',
                line=dict(
                    color=complexity_colors[complexity_name],
                    dash='dash',
                    width=2
                ),
                showlegend=True
            ),
            row=2, col=1
        )

    # Atualiza o layout dos gráficos
    fig.update_layout(
        height=1200,
        title_text="Métricas de Desempenho do Algoritmo de Ordenação",
        showlegend=True,
        legend=dict(
            yanchor="top",
            y=0.99,
            xanchor="left",
            x=1.05
        )
    )
    
    # Atualiza os eixos X e Y
    for row in [1, 2, 3]:
        fig.update_xaxes(title_text="Tamanho da Entrada", type="log", row=row, col=1)
    
    fig.update_yaxes(title_text="Número de Movimentações", type="log", row=1, col=1)
    fig.update_yaxes(title_text="Tempo (segundos)", type="log", row=2, col=1)
    fig.update_yaxes(title_text="Número de Comparações", type="log", row=3, col=1)
    
    return fig

def main():
    # Lê os arquivos de dados
    movimentacoes_df = read_data_file('movimentacoes.txt')
    tempo_df = read_data_file('tempo.txt')
    comparacoes_df = read_data_file('comparacoes.txt')
    
    # Cria os gráficos
    fig = create_plot(movimentacoes_df, tempo_df, comparacoes_df)
    
    # Salva o gráfico como HTML interativo
    fig.write_html('metricas_ordenacao.html')
    
    # Opcional: Mostra o gráfico diretamente
    fig.show()

if __name__ == "__main__":
    main()